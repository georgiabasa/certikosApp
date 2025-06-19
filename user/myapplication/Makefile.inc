# -*-Makefile-*-

OBJDIRS		+= $(USER_OBJDIR)/myapplication

USER_PING_SRC	+= $(USER_DIR)/myapplication/p1.c
USER_PING_OBJ	:= $(patsubst %.c, $(OBJDIR)/%.o, $(USER_PING_SRC))
USER_PING_OBJ	:= $(patsubst %.S, $(OBJDIR)/%.o, $(USER_PING_OBJ))
KERN_BINFILES	+= $(USER_OBJDIR)/myapplication/p1

USER_PONG_SRC	+= $(USER_DIR)/myapplication/p2.c
USER_PONG_OBJ	:= $(patsubst %.c, $(OBJDIR)/%.o, $(USER_PONG_SRC))
USER_PONG_OBJ	:= $(patsubst %.S, $(OBJDIR)/%.o, $(USER_PONG_OBJ))
KERN_BINFILES	+= $(USER_OBJDIR)/myapplication/p2

USER_DING_SRC	+= $(USER_DIR)/myapplication/p3.c
USER_DING_OBJ	:= $(patsubst %.c, $(OBJDIR)/%.o, $(USER_DING_SRC))
USER_DING_OBJ	:= $(patsubst %.S, $(OBJDIR)/%.o, $(USER_DING_OBJ))
KERN_BINFILES	+= $(USER_OBJDIR)/myapplication/p3

my_application: $(USER_OBJDIR)/myapplication/p1 \
          $(USER_OBJDIR)/myapplication/p2 \
          $(USER_OBJDIR)/myapplication/p3 \

$(USER_OBJDIR)/myapplication/p1: $(USER_LIB_OBJ) $(USER_PING_OBJ) $(USER_MYAPPLICATION_OBJ)
	@echo + ld[USER/p1] $@
	$(V)$(LD) -o $@ $(USER_LDFLAGS) $(USER_LIB_OBJ) $(USER_PING_OBJ) $(USER_MYAPPLICATION_OBJ) $(GCC_LIBS)
	$(V)$(OBJDUMP) -S $@ > $@.asm
	$(V)$(NM) -n $@ > $@.sym

$(USER_OBJDIR)/myapplication/p2: $(USER_LIB_OBJ) $(USER_PONG_OBJ) $(USER_MYAPPLICATION_OBJ)
	@echo + ld[USER/p2] $@
	$(V)$(LD) -o $@ $(USER_LDFLAGS) $(USER_LIB_OBJ) $(USER_PONG_OBJ) $(USER_MYAPPLICATION_OBJ) $(GCC_LIBS)
	$(V)$(OBJDUMP) -S $@ > $@.asm
	$(V)$(NM) -n $@ > $@.sym

$(USER_OBJDIR)/myapplication/p3: $(USER_LIB_OBJ) $(USER_DING_OBJ) $(USER_MYAPPLICATION_OBJ)
	@echo + ld[USER/p3] $@
	$(V)$(LD) -o $@ $(USER_LDFLAGS) $(USER_LIB_OBJ) $(USER_DING_OBJ) $(USER_MYAPPLICATION_OBJ) $(GCC_LIBS)
	$(V)$(OBJDUMP) -S $@ > $@.asm
	$(V)$(NM) -n $@ > $@.sym

$(USER_OBJDIR)/myapplication/%.o: $(USER_DIR)/myapplication/%.c
	@echo + cc[USER/myapplication] $<
	@mkdir -p $(@D)
	$(V)$(CC) $(USER_CFLAGS) -c -o $@ $<

$(USER_OBJDIR)/myapplication/%.o: $(USER_DIR)/myapplication/%.S
	@echo + as[USER/myapplication] $<
	@mkdir -p $(@D)
	$(V)$(CC) $(USER_CFLAGS) -c -o $@ $<

	@echo + cc[USER/myapplication] $<
	@mkdir -p $(@D)
	$(V)$(CC) $(USER_CFLAGS) -c -o $@ $<
