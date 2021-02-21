# Names to modify
PROG        = minesweeper
ARCHIVENAME = draescherl-tp9
DOXYNAME    = Minesweeper

# Directories
SRCDIR      = src/
INCDIR      = include/
BINDIR      = bin/
DOCDIR      = doc/
SAVDIR      = save/

# Files
DOXYFILE    = Doxyfile
README      = README.md
MAKEFILE    = Makefile
GITIGNORE   = .gitignore
SRC         = $(wildcard $(SRCDIR)*.c)
HEAD        = $(wildcard $(INCDIR)*.h)
OBJ         = $(subst $(SRCDIR), $(BINDIR), $(SRC:.c=.o))

# Commands
CP          = cp -r
TAR         = tar -cvzf
RM          = rm -rf
MKDIR       = mkdir -p

# Compiler
CC          = gcc
CFLAGS      = -Wall -Iinclude
LDFLAGS     = -lm

# Compilation
all: $(PROG)
$(PROG): $(OBJ) $(HEAD)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(BINDIR)%.o: $(SRCDIR)%.c
	$(CC) -c $(CFLAGS) $< -o $@ $(LDFLAGS)

# Remove .o files
.PHONY: clean
clean: 
	$(RM) $(OBJ)*

# Delete output bin/ doc/ save/
.PHONY: mrproper
mrproper: 
	$(RM) $(PROG)
	$(RM) $(BINDIR)
	$(RM) $(DOCDIR)
	$(RM) $(SAVDIR)

# Generate documentation
.PHONY: doc
doc:
	$(MKDIR) $(DOCDIR)
	doxygen -g
	sed -i '/INPUT                  =/c\INPUT                  = $(SRCDIR) $(INCDIR) $(README)' $(DOXYFILE)
	sed -i '/OUTPUT_DIRECTORY       =/c\OUTPUT_DIRECTORY       = $(DOCDIR)' $(DOXYFILE)
	sed -i '/PROJECT_NAME           =/c\PROJECT_NAME           = "$(DOXYNAME)"' $(DOXYFILE)
	sed -i '/USE_MDFILE_AS_MAINPAGE =/c\USE_MDFILE_AS_MAINPAGE = $(README)' $(DOXYFILE)
	doxygen $(DOXYFILE)
	$(RM) $(DOXYFILE)

# Save code
.PHONY: save
save:
	$(CP) $(INCDIR) $(SAVDIR)
	$(CP) $(SRCDIR) $(SAVDIR)

# Prepare archive to give in
.PHONY: archive
archive:
	$(MKDIR) $(ARCHIVENAME)
	$(CP) $(INCDIR) $(ARCHIVENAME)
	$(CP) $(SRCDIR) $(ARCHIVENAME)
	$(CP) $(MAKEFILE) $(ARCHIVENAME)
	$(CP) $(README) $(ARCHIVENAME)
	$(TAR) $(ARCHIVENAME).tgz $(ARCHIVENAME)/
	$(RM) $(ARCHIVENAME)

# Create .gitignore
.PHONY: git
git:
	@touch -a $(GITIGNORE)
	@echo "$(DOCDIR)" >> $(GITIGNORE)
	@echo "$(BINDIR)" >> $(GITIGNORE)
	@echo "$(SAVDIR)" >> $(GITIGNORE)
	@echo "$(PROG)" >> $(GITIGNORE)

# Prepare folders for compilation
.PHONY: prepare
prepare:
	$(MKDIR) $(SRCDIR) $(BINDIR) $(DOCDIR) $(SAVDIR) $(INCDIR)
	@touch -a $(README)

# Print help to terminal
.PHONY: usage
usage:
	@echo '-----Usage-----'
	@echo '[+] Prepare necessary folders                      make prepare'
	@echo '[+] Create .gitignore                              make git'
	@echo '[+] Compile program                                make'
	@echo '[+] Remove compilation objects                     make clean'
	@echo '[+] Generate documentation                         make doc'
	@echo '[+] Remove everything that is not source code      make mrproper'
	@echo '[+] Save current state of code                     make save'
	@echo '[+] Archive project                                make archive'