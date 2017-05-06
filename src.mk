SRC      := init.c loop.c lprintf.c main.c table.c uninit.c
SRC_DB   := blk.c grow.c init.c load.c rlock.c unload.c unlock.c wlock.c
SRC_INIT := config.c signal.c socket.c thread.c
SRC_OP   := 21_create.c #2f_delete.c
SRC_OP   += 30_insert.c 31_select.c 32_update.c 33_delete.c
SRC_OP   += 40_equ.c 41_neq.c 50_set.c
SRC_OP   += ff_ping.c
SRC_SY   := asn.c cmp.c error.c fatal.c getpair.c log.c read.c time.c
SRC_TAB  := by_label.c delete.c ent.c field.c foff.c foreach.c match.c select.c
SRC_TAB  += update.c

SRC      += $(addprefix db/,$(SRC_DB))
SRC      += $(addprefix init/,$(SRC_INIT))
SRC      += $(addprefix op/op_,$(SRC_OP))
SRC      += $(addprefix sy/,$(SRC_SY))
SRC      += $(addprefix tab/,$(SRC_TAB))
SRC      := $(addprefix src/,$(SRC))
