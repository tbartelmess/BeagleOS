task :default => :build

task :increment_version do
  version = if File.exist?('VERSION')
              File.read('VERSION').to_i + 1
            else
              0
            end
  File.open('VERSION', 'w') do |fd|
    fd.puts version
  end
end

task build: [:increment_version] do
  cmds = []

  cmds << "cd beagleos"
  cmds << "echo Cleaning"
  cmds << "make clean"
  cmds << "touch Makefile"
  cmds << "echo Building"
  cmds << "make"
  cmds << "echo Copying to TFTP Server"
  cmds << "cp -v beagleOS.bin /var/lib/tftpboot/beagleOS.bin"

  cmds = cmds.compact.join ' && '

  sh "rsync -trulip --exclude '.git/' ./ beagle:~/beagleos"
  sh "ssh beagle '#{cmds}'"
end
