[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/76mHqLr5)
# Description

Linux shell implemented in C.

# Assumptions

#### Specification 3 : warp

- When warp is used for the very first time with the `-` argument shell warps to the home directory since there is no previous working directory.
- In case of multiple arguments for warp, even if one of it fails the rest are executed sequentially from left to right.

#### Specification 4 : peek

- ASCII values are used as comparators to sort files and directories in lexicographic order.
- All files with execute permission are treated as executables and coloured green.

#### Specification 5 : pastevents commands
- Background processes from the pastevents are executed as foreground processes when `pastevents execute <index>` is used. 

#### Specification 6 : System commands 
- When multiple commands are used together with `;`, if the last command takes more than 2 seconds to execute then the last command is displayed in the next prompt.

#### Specification 8 : seek

- If the given file name does not have an extension, then all files with that name and any extension are displayed and counted as matches.
