SRC      := init.c loop.c main.c table.c uninit.c
SRC_DB   := grow.c init.c load.c rlock.c unload.c unlock.c wlock.c
SRC_INIT := config.c signal.c socket.c thread.c
SRC_OP   := # todo
SRC_SY   := # todo
SRC_TAB  := # todo

SRC      += $(addprefix db/,$(SRC_DB))
SRC      += $(addprefix init/,$(SRC_INIT))
SRC      += $(addprefix op/,$(SRC_OP))
SRC      += $(addprefix sy/,$(SRC_SY))
SRC      += $(addprefix tab/,$(SRC_TAB))
SRC      := $(addprefix src/,$(SRC))
