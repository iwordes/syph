SRC     := init.c main.c uninit.c
SRC_DB  := # todo
SRC_REQ := # todo
SRC_RES := # todo
SRC_SY  := # todo

SRC     += $(addprefix db/,$(SRC_DB))
SRC     += $(addprefix req/,$(SRC_REQ))
SRC     += $(addprefix res/,$(SRC_RES))
SRC     += $(addprefix sy/,$(SRC_SY))
SRC     := $(addprefix src/,$(SRC))
