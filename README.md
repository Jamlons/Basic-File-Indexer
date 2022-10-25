# Basic File Indexer
#### Tested only on Ubuntu 18.04

This program allows you to create an index file, this file stores the readable strings from a set of files - filelist. Once the index file is created, it then allows you to search for a word within that index file returning all file paths that include said word.

This program includes a Makefile, allowing for easy cmd compiling. To use all you have to do is enter 'make' in the cmd line.
- Make sure you have make installed on your Ubuntu machine


An index file can be created or updated by invoking ./trove [-f filename] [-l length] [-b | -r | -u] [filelist] on the cmd line.

-f being an optional filename you want the index file to be called (default name is /tmp/trove).

-l sets the maximum required length of alphanumeric words to be stored, must be positive. Default is 4.

-b building an index file, doing so deletes the old file and replaces the information stored within using the filelist.

-r removes all files included within filelist for the given index file. Making them non-searchable.

-u updates all files included within filelist for the given index file, removing the old search info if required.


An index file can then be searched by invoking ./trove [-f filename] word

-f being the optional filename to search inside of (default is /tmp/trove).


##### An example of the code follows:

`./trove -l 5 -b README.md trove.c`

This will store all alphanumeric found strings inside both README.md and trove.c that are atleast 5 characters long.

`./trove ubuntu`

This will return the full filepath of README.txt within the cmd line, as only it includes the string 'ubuntu'.
