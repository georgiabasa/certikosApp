# -*-Makefile-*-

OBJDIRS		+= $(USER_OBJDIR)/rbac

USER_PING_SRC	+= $(USER_DIR)/rbac/p1.c
USER_PING_OBJ	:= $(patsubst %.c, $(OBJDIR)/%.o, $(USER_PING_SRC))
USER_PING_OBJ	:= $(patsubst %.S, $(OBJDIR)/%.o, $(USER_PING_OBJ))
KERN_BINFILES	+= $(USER_OBJDIR)/rbac/p1

USER_PONG_SRC	+= $(USER_DIR)/rbac/p2.c
USER_PONG_OBJ	:= $(patsubst %.c, $(OBJDIR)/%.o, $(USER_PONG_SRC))
USER_PONG_OBJ	:= $(patsubst %.S, $(OBJDIR)/%.o, $(USER_PONG_OBJ))
KERN_BINFILES	+= $(USER_OBJDIR)/rbac/p2

USER_DING_SRC	+= $(USER_DIR)/rbac/p3.c
USER_DING_OBJ	:= $(patsubst %.c, $(OBJDIR)/%.o, $(USER_DING_SRC))
USER_DING_OBJ	:= $(patsubst %.S, $(OBJDIR)/%.o, $(USER_DING_OBJ))
KERN_BINFILES	+= $(USER_OBJDIR)/rbac/p3

USER_RBAC_SRC	:= $(USER_DIR)/rbac/rbac.c
USER_RBAC_OBJ	:= $(patsubst %.c, $(OBJDIR)/%.o, $(USER_RBAC_SRC))

rbac: $(USER_OBJDIR)/rbac/p1 \
          $(USER_OBJDIR)/rbac/p2 \
          $(USER_OBJDIR)/rbac/p3 \

$(USER_OBJDIR)/rbac/p1: $(USER_LIB_OBJ) $(USER_PING_OBJ) $(USER_RBAC_OBJ)
	@echo + ld[USER/p1] $@
	$(V)$(LD) -o $@ $(USER_LDFLAGS) $(USER_LIB_OBJ) $(USER_PING_OBJ) $(USER_RBAC_OBJ) $(GCC_LIBS)
	$(V)$(OBJDUMP) -S $@ > $@.asm
	$(V)$(NM) -n $@ > $@.sym

$(USER_OBJDIR)/rbac/p2: $(USER_LIB_OBJ) $(USER_PONG_OBJ) $(USER_RBAC_OBJ)
	@echo + ld[USER/p2] $@
	$(V)$(LD) -o $@ $(USER_LDFLAGS) $(USER_LIB_OBJ) $(USER_PONG_OBJ) $(USER_RBAC_OBJ) $(GCC_LIBS)
	$(V)$(OBJDUMP) -S $@ > $@.asm
	$(V)$(NM) -n $@ > $@.sym

$(USER_OBJDIR)/rbac/p3: $(USER_LIB_OBJ) $(USER_DING_OBJ) $(USER_RBAC_OBJ)
	@echo + ld[USER/p3] $@
	$(V)$(LD) -o $@ $(USER_LDFLAGS) $(USER_LIB_OBJ) $(USER_DING_OBJ) $(USER_RBAC_OBJ) $(GCC_LIBS)
	$(V)$(OBJDUMP) -S $@ > $@.asm
	$(V)$(NM) -n $@ > $@.sym

$(USER_OBJDIR)/rbac/%.o: $(USER_DIR)/rbac/%.c
	@echo + cc[USER/rbac] $<
	@mkdir -p $(@D)
	$(V)$(CC) $(USER_CFLAGS) -c -o $@ $<

$(USER_OBJDIR)/rbac/%.o: $(USER_DIR)/rbac/%.S
	@echo + as[USER/rbac] $<
	@mkdir -p $(@D)
	$(V)$(CC) $(USER_CFLAGS) -c -o $@ $<

$(USER_OBJDIR)/rbac/rbac.o: $(USER_DIR)/rbac/rbac.c
	@echo + cc[USER/rbac] $<
	@mkdir -p $(@D)
	$(V)$(CC) $(USER_CFLAGS) -c -o $@ $<
