task :default => :build

task :build do
  cmds = []
  env = []

  cmds << "cd beagleos"
  cmds << "echo Cleaning"
  cmds << "make clean"
  cmds << "touch Makefile"
  cmds << "echo Building"
  cmds << "make"
  cmds << "echo Copying to TFTP Server"
  cmds << "cp -v beagleOS.bin /srv/tftp/beagleOS.bin"

  cmds = cmds.compact.join ' && '

  sh "rsync -trulip --exclude '.git/' . pi:/home/mrada/beagleos"
  sh "ssh mrada@ferrous-pi.local '#{cmds}'"
end
