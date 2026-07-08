


MODULE_SRC= mlx_image.swift mlx_window.swift mlx_init.swift
MODULE_OBJ=$(MODULE_SRC:.swift=.swiftmodule)

SRC= interface.swift $(MODULE_SRC)
OBJ=$(SRC:.swift=.o)

C_SRC= mlx_xpm.c mlx_png.c mlx_string_put.c
C_OBJ=$(C_SRC:.c=.o)
CFLAGS=-O3

NAME=libmlx.dylib

INC=-I.
#OPTI=-Ounchecked

all: $(NAME)

$(NAME): $(MODULE_OBJ) $(OBJ) $(C_OBJ)
	swiftc $(OPTI) $(INC) -o $(NAME) -emit-library $(OBJ) $(C_OBJ) -lz



%.o: %.swift
	swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@

%.swiftmodule: %.swift
	swiftc $(OPTI) $(INC) -parse-as-library -emit-module -emit-module-path $@ -module-name $(patsubst %.swift,%,$<) -module-link-name $(patsubst %.swift,%,$<) $<

# Inter-module build order (each file imports the modules listed below).
# Needed so the .swiftmodule interfaces exist before dependents compile,
# even under parallel make (-j).
mlx_window.swiftmodule: mlx_image.swiftmodule
mlx_init.swiftmodule: mlx_image.swiftmodule mlx_window.swiftmodule
mlx_image.o: mlx_image.swiftmodule
mlx_window.o: mlx_image.swiftmodule mlx_window.swiftmodule
mlx_init.o: mlx_image.swiftmodule mlx_window.swiftmodule mlx_init.swiftmodule
interface.o: mlx_image.swiftmodule mlx_window.swiftmodule mlx_init.swiftmodule

clean:
	rm -f $(NAME) $(OBJ) $(MODULE_OBJ) $(C_OBJ) *.swiftdoc *.abi.json *~

