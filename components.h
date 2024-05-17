//
// Created by sidne on 14/05/2024.
//

#ifndef PROJETO_GESTAO_DE_EVENTOS_COMPONENTS_H
#define PROJETO_GESTAO_DE_EVENTOS_COMPONENTS_H

/**
 * @brief Imprime uma linha divisória com 100 caracteres de largura.
 *
 * Esta função imprime uma linha divisória com 100 caracteres de largura
 * utilizando o caractere '='. Ela é útil para separar seções de texto
 * em uma interface de console.
 */
void imprimirLinhaDivisoria();

/**
 * @brief Imprime um título e, opcionalmente, um subtítulo, ambos centralizados,
 * dentro de uma moldura de 100 caracteres de largura.
 *
 * @param titulo O título a ser impresso. Deve ser uma string válida.
 * @param subtitulo O subtítulo a ser impresso. Pode ser NULL se nenhum subtítulo for necessário.
 *
 * @return Retorna 0 se a função for executada com sucesso.
 *
 * Esta função centraliza o título e o subtítulo dentro de uma moldura de
 * 100 caracteres de largura e os imprime na tela. Se o subtítulo for NULL,
 * apenas o título será impresso. Se o comprimento do título ou do subtítulo
 * for maior que a largura disponível, o texto será truncado.
 */
int imprimirTituloCabecario(const char *titulo, const char *subtitulo);

int imprimirRodape();

void opcaoInvalida();

#endif //PROJETO_GESTAO_DE_EVENTOS_COMPONENTS_H
