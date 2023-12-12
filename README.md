# Simple Shell Project

This is a basic implementation of a shell in C programming language. The shell supports fundamental command execution, built-in commands, and simple command piping.

## Features

- Execute external commands
- Built-in commands (e.g., cd, exit)
- Command piping

## Getting Started

### Prerequisites

- C Compiler (e.g., GCC)

### Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/MahmoudElSherbinee/simple_shell.git
    ```

2. Compile the shell:

    ```bash
    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
    cd simple-shell
    make
    ```

### Usage

Run the shell:

```bash
./hsh
```
### TEST

```In_interactive_mode:

$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```

```In_non_interactive_mode:

$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```


## Lessons Learned

Working on this simple shell project has been an enriching experience, providing valuable insights into various aspects of system programming and software development. Here are some key takeaways:

### 1. Understanding System Calls

Implementing a shell required a deep dive into system calls and process management. I gained a better understanding of how the operating system handles processes, file descriptors, and communication between different components.

### 2. Parsing and Tokenization

The process of parsing user input and tokenization became a crucial aspect of this project. Learning to handle command-line arguments, separate commands, and interpret user intentions contributed significantly to my understanding of language processing.

### 3. Handling Input/Output Redirection

Implementing features like command piping and input/output redirection shed light on how shells manage data streams. This knowledge is fundamental to understanding how complex commands are executed in a Unix-like environment.

### 4. Building a Foundation for Future Projects

This simple shell project served as a stepping stone for more complex endeavors. It laid the groundwork for exploring advanced topics in systems programming, shell scripting, and even contributing to open-source shell projects.

### 5. Collaboration and Contribution

Engaging with the open-source community and contributing to projects like shells provides valuable insights into collaborative development. Code reviews, discussions, and feedback from peers played a crucial role in refining the quality of the project.

In conclusion, this project not only enhanced my technical skills but also fostered a deeper appreciation for the intricate workings of shells and operating systems. The journey from conceptualization to implementation has been both challenging and rewarding, paving the way for continuous learning and growth in the field of software development.



## Conclusion

Thank you for exploring our simple shell project! We hope this shell provides a helpful foundation for understanding basic shell functionalities and serves as a starting point for more complex shell implementations.

Your contributions and feedback are highly appreciated. Feel free to reach out with any issues, suggestions, or improvements. Happy coding!
