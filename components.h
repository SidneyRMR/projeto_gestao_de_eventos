//
// Created by sidne on 14/05/2024.
//

#ifndef PROJETO_GESTAO_DE_EVENTOS_COMPONENTS_H
#define PROJETO_GESTAO_DE_EVENTOS_COMPONENTS_H
typedef enum {
    BLACK = 0,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
} Color;

typedef struct {
    Color textColor;
    Color bgColor;
} ColorScheme;

/**
 * @brief Define o esquema de cores a ser usado na interface.
 *
 * @param scheme O esquema de cores a ser definido.
 *
 * Esta função define o esquema de cores a ser usado na interface, incluindo
 * a cor do texto e a cor de fundo.
 */
void setColorScheme(ColorScheme scheme);

/**
 * @brief Obtém um esquema de cores pelo nome.
 *
 * @param name O nome do esquema de cores a ser obtido.
 * @return O esquema de cores correspondente ao nome fornecido.
 *
 * Esta função obtém um esquema de cores pelo nome especificado.
 */
ColorScheme getColorSchemeByName(const char* name);

/**
 * @brief Solicita um valor de senha centralizado.
 *
 * @param frase A frase para solicitar a senha.
 * @param tamanho O tamanho da senha a ser obtida.
 * @return A senha digitada pelo usuário.
 *
 * Esta função solicita ao usuário uma senha centralizada na tela.
 */
char* centralizarEObterValorSenha(const char *frase, int tamanho);

/**
 * @brief Imprime uma linha divisória ajustável.
 *
 * @param tamanho O tamanho da linha divisória a ser impressa.
 *
 * Esta função imprime uma linha divisória ajustável de acordo com o tamanho especificado.
 */
void imprimirLinhaDivisoriaAjustavel(int tamanho);

/**
 * @brief Imprime uma linha divisória fixa.
 *
 * Esta função imprime uma linha divisória fixa de tamanho predefinido.
 */
void imprimirLinhaDivisoria();

/**
 * @brief Imprime uma linha divisória para listas.
 *
 * Esta função imprime uma linha divisória específica para listas.
 */
void imprimirLinhaDivisoriaLista();

/**
 * @brief Imprime um título e um subtítulo centralizados em uma lista.
 *
 * @param titulo O título a ser impresso.
 * @param subtitulo O subtítulo a ser impresso.
 * @return Retorna 0 se a função for executada com sucesso.
 *
 * Esta função imprime um título e um subtítulo centralizados em uma lista.
 */
int imprimirTituloCabecarioLista(const char *titulo, const char *subtitulo);

/**
 * @brief Imprime uma linha para listas.
 *
 * Esta função imprime uma linha específica para listas.
 */
void imprimirLinhaLista();

/**
 * @brief Imprime um texto centralizado em uma lista.
 *
 * @param texto O texto a ser impresso.
 *
 * Esta função imprime um texto centralizado em uma lista.
 */
void imprimirCentralizadoLista(const char *texto);

/**
 * @brief Centraliza uma frase com dois valores.
 *
 * @param frase A frase a ser centralizada.
 * @param frase2 O segundo valor a ser centralizado.
 *
 * Esta função centraliza uma frase contendo dois valores.
 */
void centralizarFraseDoisValores(char *frase, char *frase2);

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

/**
 * @brief Imprime o nome do usuário e a data.
 *
 * @return Retorna 0 se a função for executada com sucesso.
 *
 * Esta função imprime o nome do usuário e a data atual.
 */
int imprimirUsuarioEData();


/**
 * @brief Exibe uma mensagem de opção inválida.
 *
 * Esta função exibe uma mensagem indicando que uma opção inválida foi selecionada.
 */
void opcaoInvalida();


/**
 * @brief Centraliza uma frase com uma cor específica.
 *
 * @param frase A frase a ser centralizada.
 * @param cor A cor da frase.
 *
 * Esta função centraliza uma frase com uma cor específica.
 */
void centralizarFrase(char *frase, const char *cor);


/**
 * @brief Solicita e centraliza um valor inteiro.
 *
 * @param frase A frase para solicitar o valor inteiro.
 * @return O valor inteiro fornecido pelo usuário.
 *
 * Esta função centraliza na tela uma frase solicitando ao usuário um valor inteiro
 */
int centralizarEObterValorInt(const char *frase);

/**
 * @brief Solicita e centraliza um valor de ponto flutuante.
 *
 * @param frase A frase para solicitar o valor de ponto flutuante.
 * @return O valor de ponto flutuante fornecido pelo usuário.
 *
 * Esta função centraliza na tela uma frase solicitando ao usuário um valor de ponto flutuante.
 */
double centralizarEObterValorDouble(const char *frase);

/**
 * @brief Solicita e centraliza um caractere.
 *
 * @param frase A frase para solicitar o caractere.
 * @param tamanho O tamanho do caractere a ser obtido.
 * @return O caractere fornecido pelo usuário.
 *
 * Esta função centraliza na tela uma frase solicitando ao usuário uma string e limita o tamanho da string que pode ser inserido.
 */
char* centralizarEObterValorChar(const char *frase, int tamanho);


/**
 * @brief Imprime um título e um subtítulo centralizados, com uma linha divisória dupla.
 *
 * @param titulo O título a ser impresso.
 * @param subtitulo O subtítulo a ser impresso.
 * @return Retorna 0 se a função for executada com sucesso.
 *
 * Esta função imprime um título e um subtítulo centralizados, separados por uma linha divisória dupla.
 */
int imprimirTituloCabecarioDuplo(const char *titulo, const char *subtitulo);


/**
 * @brief Centraliza uma string em uma largura específica.
 *
 * @param str A string a ser centralizada.
 * @param largura A largura desejada para a string centralizada.
 *
 * Esta função centraliza uma string dentro de uma largura especificada, adicionando espaços
 * em branco à esquerda e à direita, se necessário, para alcançar a largura desejada.
 */
void centralizarString(char *str, int largura);


#endif //PROJETO_GESTAO_DE_EVENTOS_COMPONENTS_H
