<?php
// error500.php
//header('Content-Type: text/html; charset=UTF-8');
//header("Content-Type: text/html");

// Option A: Forced syntax error (if PHP does not compile it)
// remove the semicolon below or put something that breaks the interpreter
//$a = 5 / 0; // This raises a warning, but you could force an exit(1)

// Option B: Forced error exit
exit(1); 
?>