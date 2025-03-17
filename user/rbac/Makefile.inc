# -*-Makefile-*-

OBJDIRS		+= $(USER_OBJDIR)/rbac

USER_PING_SRC	+= $(USER_DIR)/rbac/admin.c
USER_PING_OBJ	:= $(patsubst %.c, $(OBJDIR)/%.o, $(USER_PING_SRC))
USER_PING_OBJ	:= $(patsubst %.S, $(OBJDIR)/%.o, $(USER_PING_OBJ))
KERN_BINFILES	+= $(USER_OBJDIR)/rbac/admin

USER_PONG_SRC	+= $(USER_DIR)/rbac/guest.c
USER_PONG_OBJ	:= $(patsubst %.c, $(OBJDIR)/%.o, $(USER_PONG_SRC))
USER_PONG_OBJ	:= $(patsubst %.S, $(OBJDIR)/%.o, $(USER_PONG_OBJ))
KERN_BINFILES	+= $(USER_OBJDIR)/rbac/guest

USER_DING_SRC	+= $(USER_DIR)/rbac/user.c
USER_DING_OBJ	:= $(patsubst %.c, $(OBJDIR)/%.o, $(USER_DING_SRC))
USER_DING_OBJ	:= $(patsubst %.S, $(OBJDIR)/%.o, $(USER_DING_OBJ))
KERN_BINFILES	+= $(USER_OBJDIR)/rbac/user

USER_RBAC_SRC	:= $(USER_DIR)/rbac/rbac.c
USER_RBAC_OBJ	:= $(patsubst %.c, $(OBJDIR)/%.o, $(USER_RBAC_SRC))

rbac: $(USER_OBJDIR)/rbac/admin \
          $(USER_OBJDIR)/rbac/guest \
          $(USER_OBJDIR)/rbac/user \

$(USER_OBJDIR)/rbac/admin: $(USER_LIB_OBJ) $(USER_PING_OBJ) $(USER_RBAC_OBJ)
	@echo + ld[USER/admin] $@
	$(V)$(LD) -o $@ $(USER_LDFLAGS) $(USER_LIB_OBJ) $(USER_PING_OBJ) $(USER_RBAC_OBJ) $(GCC_LIBS)
	$(V)$(OBJDUMP) -S $@ > $@.asm
	$(V)$(NM) -n $@ > $@.sym

$(USER_OBJDIR)/rbac/guest: $(USER_LIB_OBJ) $(USER_PONG_OBJ) $(USER_RBAC_OBJ)
	@echo + ld[USER/guest] $@
	$(V)$(LD) -o $@ $(USER_LDFLAGS) $(USER_LIB_OBJ) $(USER_PONG_OBJ) $(USER_RBAC_OBJ) $(GCC_LIBS)
	$(V)$(OBJDUMP) -S $@ > $@.asm
	$(V)$(NM) -n $@ > $@.sym

$(USER_OBJDIR)/rbac/user: $(USER_LIB_OBJ) $(USER_DING_OBJ) $(USER_RBAC_OBJ)
	@echo + ld[USER/user] $@
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
