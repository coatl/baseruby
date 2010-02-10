

sofiles=`find install/lib/baseruby/1.8/ -name '*.so'`.split
sofiles.each{|sofile| require sofile }

sofiles<<"./baseruby"

sofile2base={}
open("/proc/#$$/maps"){|maps|
  maps.each_line{|line|
    next unless /^([0-9a-fA-F]+)-[0-9a-fA-F]+ +[^ ]{2}x[^ ] +.* ([^ ]+)\n$/===line
    offset,name=$1,$2
    offset=offset.to_i(16)
    sofile2base[name]=offset
  }
}


addr2flags={}
addr2name={}
sofiles.each{|sofile|
  full=File.expand_path sofile
  base=sofile2base[full]
  base=0 if full[/\/baseruby$/]
  syms=IO.popen "objdump -T -t #{sofile}"
  syms.each_line{|l| 
    all,addr,flags,flags2,section,offset,type,name=
      *l.match( /^([0-9a-fA-F]+) ([^ ]*) +([^ ]+) +([^ ]+)[ \t]+([0-9a-fA-F]+) {1,2}([^ ]*) +([^ ]+) *\n$/ )

    next unless all

    addr=base+addr.to_i(16)
    addr2flags[addr]=flags
    addr2name[addr]=name
  }
}


puts "The following ruby methods are static functions in c"
ObjectSpace.each_object(Module){|mod|
  (mod.instance_methods(false).map{|im| 
    im=mod.instance_method im
  }+mod.methods(false).map{|sm|
    sm=mod.method sm
  }).each{|m|
    name=m.inspect[/^#<(?:Unbound)?Method: (.*)>$/,1]
    addr=m.c_method_address
    if addr and !addr2flags[addr]
      print "#{name}=>!!!NOT_FOUND!!! #{'%x'%addr}\n"
    elsif addr and addr2flags[addr][/l/]
      print "#{name}=>#{addr2name[addr]} #{'%x'%addr}\n"
    end
  }
}

