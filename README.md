*This project has been created as part of the 42 curriculum by dsalimov, mfekhar.*

#FOR OUR USE

Minishell has 5 main parts:
1. Input & Signals
2. Lexer (Tokenization)
3. Parser
4. Executor
5. Builtins + Env management



Person A — Parsing & Structure

Responsible for:
- architecture 
- readline loop
- tokenization (lexer)
- handling quotes
- expanding $VAR and $?
- building command structure (t_cmd *cmd)
- syntax error detection
- heredoc parsing logic (only parsing, not execution)

This person produces:
t_cmd *cmd

Person B — Execution & System

Responsible for:
- pipes
- fork
- execve
- dup2
- redirections
- heredoc execution (maybe I can do this?)
- builtins execution
- env list structure (almost done)
- exit status handling
- signals (execution side)

This person receives:
t_cmd *cmd

------------------------------
echo "hello" | grep h > out.txt

Lexer
WORD(echo)
WORD("hello")
PIPE
WORD(grep)
WORD(h)
REDIR_OUT
WORD(out.txt)

Parser
cmd1->argv = ["echo", "hello", NULL];
cmd1->path = NULL;                // builtin
cmd1->redirs = NULL;              // no redirections
cmd1->infile = STDIN_FILENO;      // 0
cmd1->outfile = STDOUT_FILENO;    // 1
cmd1->pipe_out = 1;               // because of |
cmd1->next = cmd2;

t_redir *r1;
r1->type = T_REDIR_OUT; //>
r1->target = "out.txt";
r1->fd = -1;          // not opened yet
r1->next = NULL;

cmd2->argv = ["grep", "h", NULL];
cmd2->path = NULL;                // resolved during execution
cmd2->redirs = r1;
cmd2->infile = STDIN_FILENO;      // 0
cmd2->outfile = STDOUT_FILENO;    // 1
cmd2->pipe_out = 0;               // last command
cmd2->next = NULL;