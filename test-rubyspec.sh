#!/bin/sh 
(cd ../mspec; git pull; \
 cd ../rubyspec; git pull)
./baseruby -I `pwd` -I `pwd`/lib -I `pwd`/.ext -C ../rubyspec ../mspec/bin/mspec

