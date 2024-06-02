cmake_minimum_required(VERSION 3.27)
project(projeto_gestao_de_eventos C)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)
set(RESOURCE_FILES resources/resources.rc)


add_executable(CreatePDF main.c)
target_link_libraries(CreatePDF hpdf)

add_executable(projeto_gestao_de_eventos
        main.c
        produto.c
        produto.h
        usuario.c
        usuario.h
        venda.c
        venda.h
        evento/evento.c
        evento/evento.h
        menu.c
        menu.h
        venda_detalhes.c
        venda_detalhes.h
        login.c
        login.h
        variaveis_compartilhadas.c
        variaveis_compartilhadas.h
        components/components.c
        components/components.h
        ${RESOURCE_FILES}
)
