TARGETS := pingbeagleboneinstance.cdl
ADL := assembly.camkes

ProducerThreadImpl_CFILES = components/ProducerThreadImpl/src/ProducerThreadImpl.c  components/ProducerThreadImpl/src/ping.c
ProducerThreadImpl_HFILES = components/ProducerThreadImpl/include/generatedtypes.h
ConsumerThreadImpl_CFILES = components/ConsumerThreadImpl/src/ConsumerThreadImpl.c  components/ConsumerThreadImpl/src/ping.c
ConsumerThreadImpl_HFILES = components/ConsumerThreadImpl/include/generatedtypes.h
Timer_CFILES = components/timer/src/timer.c

include ${SOURCE_DIR}/../../tools/camkes/camkes.mk
