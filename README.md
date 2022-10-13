# CITS2002_project_2

The goal of this project is to design and develop a command-line utility program, named trove, to build and search a compressed index of the contents of files.
 
Successful completion of the project will develop and enhance your understanding of advanced features of the C11 programming language, core Linux and macOS system-calls, POSIX function calls, and the use of the make utility.
(Some of) the contents of all required files are to be stored in a trove-file. A trove-file will contain the absolute pathnames of the files that have been indexed, and each of the 'words' found in those files.

The words indexed by trove, are minimum-length sequences of alphanumeric characters. Some example words are:    main, Australia, and GTHO351. The character sequence COVID-19 contains 2 words, but the second word might not be stored if indexed words must be at least 3 characters long.

Naturally, if many files are indexed, or if many words are found, the trove-file has the potential to become very large. Thus, the trove-file will be compressed when stored on disk.
