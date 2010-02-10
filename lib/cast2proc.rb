
def cast2Proc procish
#this method also needs to be available to the compiler!
  if Proc===procish
    return procish
  elsif nil==procish
    return proc{}
  elsif procish.respond_to? :to_proc
    procish=procish.to_proc
    unless Proc===procish
      raise TypeError, "#{procish.class}#to_proc should return Proc"
    end
    return procish
  else
    raise TypeError, "wrong argument type #{procish.class} (expected Proc)"
  end
end

