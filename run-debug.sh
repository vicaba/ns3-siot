./waf --run scratch/ns2-mobility-trace-netanim --command-template="gdb --args %s --traceFile=/home/vcaballero/Downloads/siot_animation.tcl --profileFile=/home/vcaballero/Downloads/ausgrid.csv --nodeNum=300 --duration=2600 --logFile=traces_logs/ns2mobility.log --distanceLogFile=traces_logs/nodeDistance.tr --animationFile=traces_logs/animation.xml --outputProfilesFile=traces_logs/profiles.log"

./waf --run scratch/ns2-mobility-trace-netanim --command-template="gdb --args %s --traceFile=/home/vcaballero/Downloads/walk_only_animation.tcl --profileFile=none --nodeNum=300 --duration=2600 --logFile=traces_logs/ns2mobility.log --distanceLogFile=traces_logs/nodeDistance.tr --animationFile=traces_logs/animation.xml --outputProfilesFile=traces_logs/profiles.log"

./waf --run "scratch/ns2-mobility-trace-netanim --traceFile=/home/vcaballero/Downloads/siot_animation.tcl --profileFile=/home/vcaballero/Downloads/ausgrid.csv --nodeNum=300 --duration=2600 --logFile=traces_logs/ns2mobility.log --distanceLogFile=traces_logs/nodeDistance.tr --animationFile=traces_logs/animation.xml --outputProfilesFile=traces_logs/profiles.log"


