require "mkmf"

$readline_headers = ["stdio.h"]

def have_readline_header(header)
  if have_header(header)
    $readline_headers.push(header)
    return true
  else
    return false
  end
end

def have_readline_var(var)
  return have_var(var, $readline_headers)
end

dir_config('curses')
dir_config('ncurses')
dir_config('termcap')
dir_config("readline")
enable_libedit = enable_config("libedit")
have_library("user32", nil) if /cygwin/ === RUBY_PLATFORM
have_library("ncurses", "tgetnum") ||
  have_library("termcap", "tgetnum") ||
  have_library("curses", "tgetnum")

  unless (have_readline_header("editline/readline.h") ||
          have_readline_header("readline/readline.h")) &&
          have_library("edit", "readline")
    exit
  end

have_func("rl_filename_completion_function")
have_func("rl_username_completion_function")
have_func("rl_completion_matches")
have_readline_var("rl_deprep_term_function")
have_readline_var("rl_completion_append_character")
have_readline_var("rl_basic_word_break_characters")
have_readline_var("rl_completer_word_break_characters")
have_readline_var("rl_basic_quote_characters")
have_readline_var("rl_completer_quote_characters")
have_readline_var("rl_filename_quote_characters")
have_readline_var("rl_attempted_completion_over")
have_readline_var("rl_library_version")
have_readline_var("rl_event_hook")
have_func("rl_cleanup_after_signal")
have_func("rl_clear_signals")
have_func("rl_vi_editing_mode")
have_func("rl_emacs_editing_mode")
have_func("replace_history_entry")
have_func("remove_history")
create_makefile("readline")
