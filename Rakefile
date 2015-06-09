task :default => :build


task :build do
  cmds = []
  env = []

  cmds << "cd beagleos"
  cmds << "echo ==> Cleaning"
  cmds << "make clean"
  cmds << "touch Makefile"
  cmds << "echo ==> Building"
  cmds << "make"

  cmds = cmds.compact.join ' && '

  sh 'rsync -trulip . mrada@ferrous-pi.local:/home/mrada/beagleos'
  sh "ssh mrada@ferrous-pi.local '#{cmds}'"
end
