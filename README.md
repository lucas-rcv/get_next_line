*This project has been created as part of the 42 curriculim by lucaroma*

## Description

**get_next_line** The main goal is to code a function that returns a single line read from a file descriptor (`fd`).

Key features of the project:
* Reapeted calls to your `get_next_line()` function let you read the text file pointed to by the file descriptor, line by line, until the end of the file.
* It works both when reading from a file and when reading from standard input.
* It compiles with a definable `BUFFER_SIZE`, allowing the function to adapt to reading chunks of various sizes efficiently.

---

## Project structure

```text
.
├── get_next_line.c
├── get_next_line.h
├── get_next_line_utils.c
├── get_next_line_bonus.c
├── get_next_line_bonus.h
└── get_next_line_utils_bonus.c
```
- `get_next_line.c` contains the main function `get_next_line` and three other static functios `ft_read_line` | `ft_get_line` | `clean`.
- `get_next_line.h` contains the public prototypes and required includes.
- `get_next_line_utils.c` contains the output and number-conversion helper functions.
- `*bonus` all these files contains the bonus part.

## Algorithm Explanation & Justification

### Why a Static Variable?
In C, local variables lose their state and memory once the function execution finishes.
However `get_next_line`needs to remember what was left in the buffer from the previous call.

### How does it work?
1. **Reading & Storing:** The function allocates a buffer based on the `BUFFER_SIZE` provided at compilation. It loops using the `read()` system call, fetching chunks of data and appending them to our accumulator until it spots a newline character (`\n`) or hits the end of the file.
2. **Extracting the line:** Once a `\n` or EOF is found, we isolate everything from the start of the accumulated string up to that newline and prepare it to be returned.
3. **Saving the leftovers:** Any characters that came *after* the newline aren't lost—they are safely stored back into the static variable, waiting patiently for the next call.
4. **Keeping memory clean:** Every time we allocate memory using `malloc`, we make sure to free it responsibly once it's no longer needed, keeping memory leaks away.

---

## Instructions

### Compilation
The function is compiled together with your test files and the `BUFFER_SIZE` macro defined. For example:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

### Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```
## Resources

* **[Oceano - get_next_line explained : develop a function that reads a file line by line](https://youtu.be/8E9siq7apUU?si=LwTi2DHwiK9Hsho7)** - Watched a youtube video to grasp the fundamentals of printf and reinforce core programming concepts.
* man 2 read — Linux manual page for the read system call.+
* **[ROMULO_NS - GET_NEXT_LINE da 42 Explicado COMPLETO | Static, Read e Buffer](https://youtu.be/81wXOlB80Gk?si=1QyXUwt3zmp_No2m)** - Watched a youtube video to grasp the fundamentals of printf and reinforce core programming concepts.
* Community testers (paco / paco -s / francinette --strict) for rigorous edge-case verification.

### Use of AI

Tasks where AI was used: Explaining the mechanics of static variables in C, debugging memory leaks related to string manipulation, and structuring the logic for buffer management.

## Author

**Lucas Román** - `lucaroma`
