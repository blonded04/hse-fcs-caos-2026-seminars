# Process states

* R(unnable/unning) x
* S(leep) - `sleep` / waiting on `mutex`.
* D(uninterruptible sleep) - prints ... to file, sends ... over network.
* Z(ombie) - child process that has ended but parent didn't `wait` for it yet.
* T(racing) - process in debug mode, waiting for next command.
