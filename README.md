*This project has been created as part of the 42 curriculum by dsalimov*

#FOR INTERNAL USE

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
- heredoc execution
- builtins execution (done: pwd, env) //$_ shall be updated after each successful command or its last argument
- env list structure (done)
- exit status handling
- signals (execution side)

This person receives:
t_cmd *cmd

------------------------------
```text
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
cmd1->path = NULL;                // builtin, but resolved during execution
cmd1->redirs = NULL;              // no redirections
cmd1->infile = STDIN_FILENO;      // 0, change during open()
cmd1->outfile = STDOUT_FILENO;    // 1, change during open()
cmd1->next = cmd2;


t_redir *r1;
r1->type = T_REDIR_OUT; //>
r1->target = "out.txt";
r1->next = NULL;

cmd2->argv = ["grep", "h", NULL];
cmd2->path = NULL;                // resolved during execution
cmd2->redirs = r1;
cmd2->infile = STDIN_FILENO;      // 0, change during open()
cmd2->outfile = STDOUT_FILENO;    // 1, change during open()
cmd2->next = NULL;

==============================================
void ft_init(t_data *data) - initializing variables
void ft_print_error(char *msg) - for printing error msgs 
t_env *ft_env_search_key(t_data *data, char *search); //searches for KEY in env and returns *node
