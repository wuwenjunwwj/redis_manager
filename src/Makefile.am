include $(top_srcdir)/common.mk
bin_PROGRAMS = redis_manager
redis_manager_SOURCES= redisManager.cpp evServer.cpp urlCmd.cpp cmdProcessor.cpp redis_util/redis_client.cpp
redis_manager_LDADD = -levent  -lhiredis
