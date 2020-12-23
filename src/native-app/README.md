# Thunderbird Toasts

Provided is a Visual Studio solution which will allow you to compile the native client of the application.

To be able to compile, create a folder called "res" here and place the XPI add-on file in there. This is required as that is embedded as a resource in the executable, in order to allow for installation of the program from the same binary and easy distribution of a single executable file.

In the future, a bit of house keeping would do very well, as the source file actually got pretty big, but it is still manageable.