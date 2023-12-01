#include <windows.h>
#include <devioctl.h>
#include <ntdddisk.h>
#include <ntddscsi.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <strsafe.h>
#include <intsafe.h>
#define _NTSCSI_USER_MODE_
#include <scsi.h>
#include <errno.h>
#include "spti.h"

#define PAGE_SIZE  0x1000
#define PAGE_SHIFT 12L
#define arraysize 25

//CDB16 define
#define CDB16GENERIC_LENGTH 16

typedef struct {
    int disk;
    int write;
    int read;
    int lba;
    int sector_cnt;
    unsigned int data;
} Args;

void print_usage() {
    printf("Usage: scsi.exe --disk <disk_number> [--write|--read] --lba <lba_value> --sector_cnt <sector_count> --data <hex_data>\n");
    printf("Example: scsi.exe --disk 2 --read --lba 9 --sector_cnt 32\n");

}

int parse_args(int argc, char* argv[], Args* args) {
    memset(args, 0, sizeof(Args));

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--disk") == 0) {
            i++;
            if (i < argc) {
                args->disk = atoi(argv[i]);
                printf("Disk: %d\n", args->disk);
            }
            else {
                printf("Error: Missing disk number after --disk.\n");
                return 0;
            }
        }
        else if (strcmp(argv[i], "--write") == 0) {
            args->write = 1;
            printf("Write: %d\n", args->write);
        }
        else if (strcmp(argv[i], "--read") == 0) {
            args->read = 1;
            printf("Read: %d\n", args->read);
        }
        else if (strcmp(argv[i], "--lba") == 0) {
            i++;
            if (i < argc) {
                args->lba = atoi(argv[i]);
                printf("LBA: %d\n", args->lba);
            }
            else {
                printf("Error: Missing LBA value after --lba.\n");
                return 0;
            }
        }
        else if (strcmp(argv[i], "--sector_cnt") == 0) {
            i++;
            if (i < argc) {
                args->sector_cnt = atoi(argv[i]);
                printf("Sector Count: %d\n", args->sector_cnt);
            }
            else {
                printf("Error: Missing sector count after --sector_cnt.\n");
                return 0;
            }
        }
        else if (strcmp(argv[i], "--data") == 0) {
            i++;
            if (i < argc) {
                char* endptr;
                args->data = strtol(argv[i], &endptr, 16);
                if (*endptr != '\0') {
                    printf("Error: Invalid hex data format after --data.\n");
                    return 0;
                }
                if (args->read == 1) {
                    printf("Data: --\n");
                }
                else {
                    printf("Data: 0x%X\n", args->data);
                }
            }
            else {
                printf("Error: Missing hex data after --data.\n");

                return 0;
            }
        }
        else {
            printf("Error: Unknown argument %s.\n", argv[i]);
            print_usage();
            return 0;
        }
    }

    return 1;
}

void WriteAll(int disknum, int lba, int sector_cnt, unsigned int data) {
    TCHAR string[arraysize];
    HANDLE hUDisk;
    SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER sptdwb;
    ULONG length = 0;
    DWORD bytesReturn;
    int iRet;
    int bytesPerSector = 512;
    StringCbPrintf(string, sizeof(string), L"\\\\.\\PhysicalDrive%d", disknum);
    hUDisk = CreateFile(
        string,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );
    if (hUDisk == INVALID_HANDLE_VALUE)
    {
        printf("can not open disk\n");
        return;
    }

    int posSector = lba;   //write from sector number #, the first sector is 0
    int writeSectors = 1; //write # sectors in total
    //int posSector = 65;
    //int readSectors = 2;
    ZeroMemory(&sptdwb, sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER));
    sptdwb.sptd.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
    sptdwb.sptd.PathId = 0;
    sptdwb.sptd.TargetId = 1;
    sptdwb.sptd.Lun = 0;
    sptdwb.sptd.CdbLength = CDB16GENERIC_LENGTH; //SCSI command length
    sptdwb.sptd.DataIn = SCSI_IOCTL_DATA_OUT;
    sptdwb.sptd.SenseInfoLength = 0;
    sptdwb.sptd.DataTransferLength = bytesPerSector; //length of writing data
    sptdwb.sptd.TimeOutValue = 5;
    sptdwb.sptd.DataBuffer = malloc(sizeof(bytesPerSector));
    sptdwb.sptd.SenseInfoOffset =
        offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER, ucSenseBuf);


    for (int i = 0; i < sector_cnt; i++) {

        FillMemory(sptdwb.sptd.DataBuffer, bytesPerSector, data);
        //printf("data is %d\n", data);
        sptdwb.sptd.Cdb[0] = SCSIOP_WRITE16;
        //sptdwb.sptd.Cdb[2] = (posSector >> 56)    & 0xff;
        //sptdwb.sptd.Cdb[3] = (posSector >> 48)    & 0xff;
        //sptdwb.sptd.Cdb[4] = (posSector >> 40)    & 0xff;
        //sptdwb.sptd.Cdb[5] = (posSector >> 32)    & 0xff;     //exceed valid range, will cause overflow and undefine behavior
        sptdwb.sptd.Cdb[6] = (posSector >> 24) & 0xff;
        sptdwb.sptd.Cdb[7] = (posSector >> 16) & 0xff;
        sptdwb.sptd.Cdb[8] = (posSector >> 8) & 0xff;
        sptdwb.sptd.Cdb[9] = (posSector) & 0xff;
        //sptdwb.sptd.Cdb[10] = (writeSectors >> 24) & 0xff;
        //sptdwb.sptd.Cdb[11] = (writeSectors >> 16) & 0xff;
        sptdwb.sptd.Cdb[12] = (writeSectors >> 8) & 0xff;
        sptdwb.sptd.Cdb[13] = (writeSectors) & 0xff;

        length = sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER);
        iRet = DeviceIoControl(hUDisk,
            IOCTL_SCSI_PASS_THROUGH_DIRECT,
            &sptdwb,
            length,
            &sptdwb,
            length,
            &bytesReturn,
            FALSE);
        if (0 == iRet) {
            printf("write failed\n");
            return;
        }
        posSector++;
    }
    CloseHandle(hUDisk);
    return;
}

void ReadPage(int disknum, int lba, int sector_cnt) {
    TCHAR string[arraysize];
    HANDLE hUDisk;
    SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER sptdwb;
    ULONG length = 0;
    DWORD bytesReturn;
    BYTE bufDataRead[32 * 1024 + 10];
    int iRet;
    StringCbPrintf(string, sizeof(string), L"\\\\.\\PhysicalDrive%d", disknum);
    hUDisk = CreateFile(
        string,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );
    if (hUDisk == INVALID_HANDLE_VALUE)
    {
        printf("can not open disk\n");
        return;
    }

    ZeroMemory(&sptdwb, sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER));
    sptdwb.sptd.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
    sptdwb.sptd.PathId = 0;
    sptdwb.sptd.TargetId = 1;
    sptdwb.sptd.Lun = 0;
    sptdwb.sptd.CdbLength = CDB10GENERIC_LENGTH;
    sptdwb.sptd.DataIn = SCSI_IOCTL_DATA_IN;
    sptdwb.sptd.SenseInfoLength = 24;
    sptdwb.sptd.DataTransferLength = 8;
    sptdwb.sptd.TimeOutValue = 2;
    sptdwb.sptd.DataBuffer = bufDataRead;
    sptdwb.sptd.SenseInfoOffset =
        offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER, ucSenseBuf);
    sptdwb.sptd.Cdb[0] = 0x25;   //READ CAPACITY(10)
    length = sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER);
    iRet = DeviceIoControl(hUDisk,
        IOCTL_SCSI_PASS_THROUGH_DIRECT,
        &sptdwb,
        length,
        &sptdwb,
        length,
        &bytesReturn,
        NULL);
    if (0 == iRet)
    {
        printf("failed reading volume of disk.\n");
        return;
    }

    //number of sector
    int sectors = bufDataRead[0] * (1 << 24) + bufDataRead[1] * (1 << 16)
        + bufDataRead[2] * (1 << 8) + bufDataRead[3] + 1;
    //bytes in every sector
    int bytesPerSector = bufDataRead[4] * (1 << 24) + bufDataRead[5] * (1 << 16)
        + bufDataRead[6] * (1 << 8) + bufDataRead[7];
    printf("sectors=%u bytesPreSector=%u\n", sectors, bytesPerSector);


    int posSector = lba;   //read from sector number #, the first sector is 0
    int readSectors = sector_cnt; //read # sectors in total
    //int posSector = 65;
    //int readSectors = 2;
    ZeroMemory(&sptdwb, sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER));
    sptdwb.sptd.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
    sptdwb.sptd.PathId = 0;
    sptdwb.sptd.TargetId = 1;
    sptdwb.sptd.Lun = 0;
    sptdwb.sptd.CdbLength = CDB16GENERIC_LENGTH; //SCSI command length
    sptdwb.sptd.DataIn = SCSI_IOCTL_DATA_IN;
    sptdwb.sptd.SenseInfoLength = 24;
    sptdwb.sptd.DataTransferLength = bytesPerSector * readSectors; //length of reading data
    sptdwb.sptd.TimeOutValue = 2;
    sptdwb.sptd.DataBuffer = bufDataRead;
    sptdwb.sptd.SenseInfoOffset =
        offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER, ucSenseBuf);

    sptdwb.sptd.Cdb[0] = SCSIOP_READ16;
    //sptdwb.sptd.Cdb[2] = (posSector >> 56)    & 0xff;
    //sptdwb.sptd.Cdb[3] = (posSector >> 48)    & 0xff;
    //sptdwb.sptd.Cdb[4] = (posSector >> 40)    & 0xff;
    //sptdwb.sptd.Cdb[5] = (posSector >> 32)    & 0xff;     //exceed valid range, will cause overflow and undefine behavior
    sptdwb.sptd.Cdb[6] = (posSector >> 24) & 0xff;
    sptdwb.sptd.Cdb[7] = (posSector >> 16) & 0xff;
    sptdwb.sptd.Cdb[8] = (posSector >> 8) & 0xff;
    sptdwb.sptd.Cdb[9] = (posSector) & 0xff;
    sptdwb.sptd.Cdb[10] = (readSectors >> 24) & 0xff;
    sptdwb.sptd.Cdb[11] = (readSectors >> 16) & 0xff;
    sptdwb.sptd.Cdb[12] = (readSectors >> 8) & 0xff;
    sptdwb.sptd.Cdb[13] = (readSectors) & 0xff;

    length = sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER);
    iRet = DeviceIoControl(hUDisk,
        IOCTL_SCSI_PASS_THROUGH_DIRECT,
        &sptdwb,
        length,
        &sptdwb,
        length,
        &bytesReturn,
        FALSE);
    if (0 == iRet)
    {
        printf("read failed\n");
        return;
    }

    for (int i = 0; i < readSectors * bytesPerSector; i++)
    {
        if (i % 16 == 0)
        {
            if (i % 512 == 0) {
                printf("\n--------------------LBA : %d--------------------", lba);
                lba++;
            }
            printf("\n");
        }
        printf("%02X ", bufDataRead[i]);
    }
    printf("\n");
    printf("-----------------------------------------------\n");
    CloseHandle(hUDisk);
    return;
}
int main(_In_ int argc, _In_z_ char* argv[]) {

    Args* args = malloc(sizeof(Args));
    int i; //for write loop

    if (argc > 5) {
        parse_args(argc, argv, args);
    }
    else {
        print_usage();
    }

    if (1 == args->read) {

        ReadPage(args->disk, args->lba, args->sector_cnt);
    }
    else if (1 == args->write) {
        WriteAll(args->disk, args->lba, args->sector_cnt, args->data);
        printf("Done.\n");
        //ReadPage(args->disk, args->lba, args->sector_cnt);
    }
    else {
        printf("invalid action, --read or --write.\n");
    }

    //free(buffer);
    free(args);

    return 0;
}
