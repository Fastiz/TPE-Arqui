# Simple Operating System

## About
Assignment for course 'Arquitectura de Computadoras' (Computer Architecture).

Simple operating system written in C and ASM based from [x64BareBones](https://bitbucket.org/RowDaBoat/x64barebones/wiki/Home).

## Compilation
First install [qemu](https://www.qemu.org/).

The compilation will be done inside a docker image because of old gcc compatibility issues.

Pull docker image:  
`docker pull agodio/itba-so:1.0`  

Run container sharing the volume of the source files:  
`docker run -v ${PWD}:/root --security-opt seccomp:unconfined -ti agodio/itba-so:1.0 //replace ${PWD} with sources root`  

Now inside the container run:  
`cd Toolchain`  
`make all`  
`cd ..`  
`make all`  

Then exit the container:  
`exit`  


## How to run and what can you do
After compilation go to sources root and:  
`./run.sh`  

You should now see a console inside a qemu window if everything worked fine. Enter 'man' as the console says to see the following options:  

* **invOp** tests what that when an invalid operation occurs then the registries are printed into console and the corresponding error is shown
* **div0** as invOp tests that a division by zero is correctly handled by the OS
* **echo** simple echo program that prints into stdout
* **time** shows hour:minutes:seconds in stdout
* **clock** digital clock that displays the drawing capabilities of the system and shows the use of a beep sound
* **clear** clears the console
* **frog** simple print of ascii frog into stdout
* **theme** used in conjunction with one of the following parameters: 'text', 'consoletext', 'error' and 'background'. Changes the color in which the system prints the different components of the console. ie, `theme text` will change the color in which stdout is printed.
