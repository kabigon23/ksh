
# KSH Shell

A simple shell (command-line interpreter) implemented in C, named "KSH." This shell allows you to execute basic commands and provides some built-in functionality similar to a Unix shell.

## Features

- Reads and executes commands from user input
- Supports basic Unix commands using `execvp()`
- Built-in commands: 
  - `cd`: Change directory
  - `help`: List built-in commands
  - `exit`: Exit the shell
- Splits user input into tokens and executes accordingly
- Supports multiple arguments and reallocation of buffers as needed

## Requirements

- GCC or any compatible C compiler
- POSIX-compatible system (Linux, MacOS, etc.)

## Building the Project

1. Clone this repository:
   ```bash
   git clone "https://github.com/kabigon23/ksh.git"
   ```
2. Navigate to the project directory:
   ```bash
   cd ksh-shell
   ```
3. Compile the code:
   ```bash
   gcc -o ksh ksh.c
   ```
   This will generate an executable named `ksh`.

## Running the Shell

After building the project, run the shell with:
```bash
./ksh
```
You should see a prompt:
```
>
```
You can then start typing commands.

## How to Use

- **Execute Unix Commands**:  
  You can type any command available in your system's PATH (e.g., `ls`, `echo Hello`, `mkdir test`) and press Enter.

- **Built-in Commands**:
  - **`cd [directory]`**:  
    Changes the current working directory to the specified `directory`.  
    Example:
    ```bash
    > cd /home/user
    ```
  - **`help`**:  
    Displays the built-in commands.
    ```bash
    > help
    cd
    help
    exit
    ```
  - **`exit`**:  
    Exits the shell.
    ```bash
    > exit
    ```

## Code Structure

- **`ksh_read_line()`**:  
  Reads a line of input from the user.

- **`ksh_split_line()`**:  
  Splits the input line into tokens (words).

- **`ksh_launch()`**:  
  Creates a child process to execute a non-built-in command using `execvp()`.

- **`ksh_cd()`**:  
  Changes the directory as a built-in command.

- **`ksh_help()`**:  
  Displays the help message listing all built-in commands.

- **`ksh_exit()`**:  
  Exits the shell loop.

- **`ksh_execute()`**:  
  Executes a command by checking if it's a built-in or external command.

- **`ksh_loop()`**:  
  The main loop that keeps prompting the user for input until `exit` is called.

## License

This project is open-source and created for educational purposes. It was developed as a personal project for learning and reference, using resources and examples found on external websites. Feel free to use, modify, and share it in accordance with the [MIT License](LICENSE).

## Contributing

Feel free to submit pull requests or open issues to enhance the functionality of this simple shell.
