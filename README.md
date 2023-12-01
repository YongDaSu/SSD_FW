# SSD_FW

## Lab01
### Requirement 01
1. Print "Your information" through UART
* After typing "info", SSD should output
  * your name in english
  * your student ID

 ### Requirement 02
1. Complete the "read“ & “write” command.
* There is only a faction of page been printed through UART, please make the whole pages in one block output by a single command.
* Hint: There are 512 Byte in one LBA sector, and 256 pages in one block.

## Lab02

### Requirement
The homework should be a CLI application and contains the following features:
* Input argument parser
* SCSI command READ16 and WRITE16
* Be able to print out some information in console
* Argument parser
--disk + %d: to select disk (You can get the info under Windows: 磁碟管理).
--write and --read: to select operation to perform.
--lba + %d: to specify starting logical block address to perform operation on SSD.
--sector_cnt + %d: the data length from starting logical block address to end.
--data + %x: set the pattern to be write into SSD (e.g., --data FF will write FF into SSD from start to end for the length of sector_cnt)
* Write Usage : scsi.exe --disk 2 --write --lba 10 --sector_cnt 32 --data aa
* Read Usage : scsi.exe --disk 2 --read --lba 9 --sector_cnt 32
