SRC = Base58.cpp IntGroup.cpp Main.cpp Bloom.cpp Random.cpp \
      Timer.cpp Int.cpp IntMod.cpp Point.cpp SECP256K1.cpp \
      KeyHunt.cpp hash/ripemd160.cpp hash/sha256.cpp hash/sha512.cpp \
      hash/ripemd160_sse.cpp hash/sha256_sse.cpp hash/keccak160.cpp \
      GmpUtil.cpp CmdParse.cpp Bech32.cpp

OBJDIR = obj

# Common objects
OBJET = $(addprefix $(OBJDIR)/, \
        Base58.o IntGroup.o Main.o Bloom.o Random.o Timer.o Int.o \
        IntMod.o Point.o SECP256K1.o KeyHunt.o hash/ripemd160.o \
        hash/sha256.o hash/sha512.o hash/ripemd160_sse.o \
        hash/sha256_sse.o hash/keccak160.o GmpUtil.o CmdParse.o Bech32.o)

# GPU specific
ifdef gpu
SRC += GPU/GPUGenerate.cpp GPU/GPUEngine.cu
OBJET += $(OBJDIR)/GPU/GPUGenerate.o $(OBJDIR)/GPU/GPUEngine.o
endif

CXX        = g++
CXXFLAGS   = -m64 -mssse3 -Wno-write-strings -I. -I$(CUDA)/include
LFLAGS     = -lgmp -lpthread

ifdef gpu
CUDA       = /usr/local/cuda-12.0
CXXCUDA    = /usr/bin/g++
NVCC       ?= nvcc
ccap       = $(if $(CCAP),$(shell echo $(CCAP) | tr -d '.'),75)
CXXFLAGS   += -DWITHGPU
LFLAGS     += -L$(CUDA)/lib64 -lcudart
endif

ifdef debug
CXXFLAGS   += -g
else
CXXFLAGS   += -O2
endif

# Ensure obj directory exists before building
$(OBJDIR):
	@mkdir -p $(OBJDIR) $(OBJDIR)/GPU $(OBJDIR)/hash

# Pattern rule for .cpp files
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# Special rule for CUDA files
ifdef gpu
$(OBJDIR)/GPU/GPUEngine.o: GPU/GPUEngine.cu | $(OBJDIR)
	$(NVCC) -allow-unsupported-compiler -maxrregcount=0 --ptxas-options=-v \
	--compile --compiler-options -fPIC -ccbin $(CXXCUDA) -m64 -O2 \
	-I$(CUDA)/include -gencode=arch=compute_$(ccap),code=sm_$(ccap) \
	-o $@ -c $<
endif

all: KeyHunt

KeyHunt: $(OBJET)
	@echo "Making KeyHunt..."
	$(CXX) $(OBJET) $(LFLAGS) -o $@

clean:
	@echo "Cleaning..."
	@rm -f $(OBJDIR)/*.o $(OBJDIR)/GPU/*.o $(OBJDIR)/hash/*.o KeyHunt

.PHONY: all clean