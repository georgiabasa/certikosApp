#add hello object directory
OBJDIRS += $(USER_OBJDIR)/hello

#define source and object files for hello
USER_HELLO_SRC += $(USER_DIR)/hello/hello.c
USER_HELLO_OBJ := $(patsubst %.c, $(OBJDIR)/%.o, $(USER_HELLO_SRC))
USER_HELLO_OBJ := $(patsubst %.S, $(OBJDIR)/%.o, $(USER_HELLO_OBJ))

#specify the binary file that will be built
KERN_BINFILES += $(USER_OBJDIR)/hello/hello

#define the target that builds the hello app
hello: $(USER_OBJDIR)/hello/hello \

$(USER_OBJDIR)/hello/hello: $(USER_LIB_OBJ) $(USER_HELLO_OBJ)
	@echo + ld[USER/hello] $@
	$(V)$(LD) -o $@ $(USER_LDFLAGS) $(USER_LIB_OBJ) $(USER_HELLO_OBJ) $(GCC_LIBS)
	$(V)$(OBJDUMP) -S $@ > $@.asm
	$(V)$(NM) -n $@ > $@.sym

#rules to compile .c files in the hello folder
$(USER_OBJDIR)/hello/%.o: $(USER_DIR)/hello/%.c
	@echo + cc[USER/hello] $<
	@mkdir -p $(@D)
	$(V)$(CC) $(USER_CFLAGS) -c -o $@ $<

#rules to compile .S files in the hello folder (if any)
$(USER_OBJDIR)/hello/%.o: $(USER_DIR)/hello/%.S
	@echo + as[USER/hello] $<
	@mkdir -p $(@D)
	$(V)$(CC) $(USER_CFLAGS) -c -o $@ $<
