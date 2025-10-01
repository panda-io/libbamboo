set -e

main() {
  clean
  cmake .
  make
}

clean() {
  git clean -d -x -f
  rm -fr tests/run-test-suite
  git worktree prune
}

main "$@"