*This project has been created as part of the 42 curriculum by asando, eynaksho.*

---

# 🐚 Minishell — As beautiful as a shell

## Description

**Minishell** is a lightweight, Unix shell implemented in C as part of the 42 School curriculum. The goal is to recreate the core behavior of **Bash**, providing a deep understanding of how a shell works under the hood — from parsing user input all the way to process management, file descriptors, pipes, and signal handling.

The project covers:
- **Lexical analysis** — tokenizing raw input into meaningful units (words, operators, redirections)
- **Variable expansion** — resolving `$VAR`, `$?`, and handling single/double quotes
- **Parsing** — building an internal command structure from tokens
- **Execution** — running commands via `execve`, managing pipes, redirections, and heredocs
- **Built-in commands** — native implementations that do not spawn child processes
- **Signal handling** — proper `ctrl-C`, `ctrl-D`, and `ctrl-\` behavior in interactive mode

---

## Features

| Feature | Details |
|---|---|
| **Prompt** | Displays `minishell$` while waiting for input |
| **History** | Command history via `readline` |
| **PATH resolution** | Finds executables using `$PATH`, relative, or absolute paths |
| **Single quotes `'`** | Prevents all interpretation of metacharacters |
| **Double quotes `"`** | Prevents interpretation of metacharacters except `$` |
| **Redirections** | `<` (input), `>` (output), `>>` (append), `<<` (heredoc) |
| **Pipes `\|`** | Chains commands, connecting stdout → stdin |
| **Variable expansion** | `$VAR` expands to its value from the environment |
| **`$?`** | Expands to the exit status of the last foreground command |
| **Signals** | `ctrl-C` → new prompt · `ctrl-D` → exit · `ctrl-\` → ignored |
| **Built-ins** | `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit` |
| **Memory management** | All heap allocations are properly freed (readline leaks excepted) |
| **One global variable** | Only `g_exit_status` (stores exit number only) |

### Built-in Commands

| Command | Behavior |
|---|---|
| `echo [-n]` | Prints arguments; `-n` suppresses the trailing newline |
| `cd <path>` | Changes working directory (relative or absolute path) |
| `pwd` | Prints the current working directory |
| `export [VAR=value]` | Sets or displays exported environment variables |
| `unset <VAR>` | Removes a variable from the environment |
| `env` | Prints all environment variables |
| `exit [n]` | Exits the shell with optional exit code `n` |

---

## Project Architecture

```
minishell/
├── include/
│   ├── minishell.h          # Core structs, enums, and shared prototypes
│   ├── builtin.h            # Built-in command prototypes
│   ├── env.h                # Environment management prototypes
│   ├── execution.h          # Execution prototypes
│   ├── expansion.h          # Expansion prototypes
│   ├── lexer.h              # Lexer/tokenizer prototypes
│   ├── parse.h              # Parser prototypes
│   └── signalmnshell.h      # Signal handler prototypes
├── src/
│   ├── main.c               # Entry point
│   ├── minishell_main/
│   │   ├── main_loop.c      # Main input loop
│   │   └── signal.c         # Signal handlers (interactive / exec mode)
│   ├── lexer/               # Tokenizer: splits input into tokens
│   │   ├── lexer.c
│   │   ├── lexer_read.c
│   │   ├── lexer_tokenizer.c
│   │   └── lexer_utils.c
│   ├── parse/               # Builds t_cmd list from token stream
│   │   ├── parse.c
│   │   ├── parse_cmd.c
│   │   ├── parse_free_function.c
│   │   └── parse_utils.c
│   ├── expansion/           # Variable expansion and quote removal
│   │   ├── expansion.c
│   │   ├── expansion_case.c
│   │   ├── expansion_handle_quotes.c
│   │   └── expansion_utils.c
│   ├── execution/           # Command execution, pipes, redirections, heredoc
│   │   ├── execution_executor.c
│   │   ├── execution_child_process.c
│   │   ├── execution_parent_process.c
│   │   ├── execution_pipe.c
│   │   ├── execution_redirection.c
│   │   ├── execution_heredoc.c
│   │   ├── execution_path_finder.c
│   │   └── execution_process_utils.c
│   ├── builtins/            # Built-in command implementations
│   │   ├── builtin.c
│   │   ├── echo.c
│   │   ├── cd.c
│   │   ├── pwd.c
│   │   ├── export.c
│   │   ├── unset.c
│   │   ├── env.c
│   │   └── exit.c
│   └── env/                 # Environment linked-list management
│       ├── env.c
│       ├── env_init.c
│       ├── env_convert_str.c
│       └── env_utils.c
├── lib/
│   └── libft/               # Custom C standard library
└── Makefile
```

**Execution pipeline:**

```
Input string
    │
    ▼
[Lexer]  →  token list  →  [Parser]  →  t_cmd list
                                              │
                                     [Expander] (vars + quotes)
                                              │
                                     [Executor] (exec / pipe / redir)
```

---

## Instructions

### Prerequisites

- **GCC** (or any C99-compatible compiler)
- **GNU Readline** library

Install readline on Debian/Ubuntu:
```bash
sudo apt-get install libreadline-dev
```

Install readline on macOS (Homebrew):
```bash
brew install readline
```

### Compilation

```bash
# Clone the repository
git clone <repository-url>
cd minishell

# Build the project
make

# Clean object files
make clean

# Full clean (objects + binary)
make fclean

# Rebuild from scratch
make re
```

### Running

```bash
./minishell
```

The shell will display the `minishell$` prompt. Type any command as you would in Bash.

### Usage Examples

```bash
# Basic command
minishell$ ls -la

# Pipes
minishell$ ls | grep .c | wc -l

# Redirections
minishell$ echo "hello" > output.txt
minishell$ cat < output.txt >> log.txt

# Heredoc
minishell$ cat << EOF
> line one
> line two
> EOF

# Variable expansion
minishell$ export NAME=42
minishell$ echo "Hello $NAME"
Hello 42

# Exit status
minishell$ ls nonexistent
minishell$ echo $?
2

# Built-ins
minishell$ cd /tmp
minishell$ pwd
/tmp
minishell$ export FOO=bar
minishell$ env | grep FOO
FOO=bar
minishell$ unset FOO
minishell$ exit 0
```

---

## Resources

### Documentation & References

- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — The official Bash reference, used as the behavioral specification for this project
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html) — Documentation for `readline`, `add_history`, and related functions
- [Linux man pages — `execve(2)`](https://man7.org/linux/man-pages/man2/execve.2.html)
- [Linux man pages — `fork(2)`](https://man7.org/linux/man-pages/man2/fork.2.html)
- [Linux man pages — `pipe(2)`](https://man7.org/linux/man-pages/man2/pipe.2.html)
- [Linux man pages — `signal(7)`](https://man7.org/linux/man-pages/man7/signal.7.html)
- [Linux man pages — `dup2(2)`](https://man7.org/linux/man-pages/man2/dup2.2.html)
- [Code Vault — Processes & Pipes in C](https://code-vault.net/course/46qpfr4tkz:1603732431896) — Video course covering process creation, piping, and file descriptors in C; used as the primary practical reference for the execution and pipe logic

### AI Usage

AI (GitHub Copilot / ChatGPT) was used during this project in the following ways:

- **Documentation & research assistance** — Clarifying the behavior of specific system calls (`waitpid`, `dup2`) and Bash edge cases (e.g., quote nesting, `$?` in subexpressions)
- **Debugging support** — Describing symptoms and asking for potential causes of memory leaks, double-free errors, and signal race conditions
- **README drafting** — Generating the initial structure and wording of this file, reviewed and adjusted by the authors
- **Code review suggestions** — Asking for feedback on specific functions for readability and correctness; all suggestions were manually reviewed, tested, and understood before being applied

> ⚠️ All AI-generated content was critically reviewed, tested, and fully understood by both authors before being integrated into the project.

---

## Authors

| Login | Profile |
|---|---|
| **asando** | 42 Student |
| **eynaksho** | 42 Student |
