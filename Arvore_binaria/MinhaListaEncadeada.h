#ifndef DEC0006_MINHA_LISTA_ENCADEADA_H
#define DEC0006_MINHA_LISTA_ENCADEADA_H

#include <cstddef>
// std::size_t

#include "Elemento.h"
// Elemento
#include "ListaEncadeadaAbstrata.h"
#include "excecoes.h"
// ExcecaoDadoInexistente
// ExcecaoListaEncadeadaVazia
// ExcecaoNaoImplementado
// ExcecaoPosicaoInvalida

/**
 * @brief Uma lista encadeada de dados.
 * 
 * @tparam T O tipo dos dados armazenados na lista.
 */
template<typename T>
class MinhaListaEncadeada: public ListaEncadeadaAbstrata<T>
{
    //Implemente aqui as funcões marcadas com virtual na ListaEncadeadaAbstrata
    //Lembre-se de implementar o construtor e destrutor da classe
    public:
        MinhaListaEncadeada<T>(){};
        ~MinhaListaEncadeada<T>(){
            if(this->_primeiro == nullptr)
                return;
            Elemento<T>* elemento = this->_primeiro;
            Elemento<T>* elementoProximo = elemento->proximo;
            for(std::size_t i = 0; i < this->_tamanho - 1; i++){
                delete elemento;
                elemento = elementoProximo;
                elementoProximo = elementoProximo->proximo;
            }
            delete elemento;
        };

        std::size_t tamanho() const {
            return this->_tamanho;
        }; 

        bool vazia() const {
            if(this->_tamanho == 0){
                return true;
            }
            return false;
        };

        std::size_t posicao(T dado) const {
            if(this->_tamanho == 0)
                throw ExcecaoListaEncadeadaVazia();

            if(this->_primeiro->dado == dado)
                return 0;
            
            Elemento<T>* elemento = this->_primeiro->proximo;
            for(std::size_t i = 1; i < this->_tamanho; i++){
                if(elemento->dado == dado){
                    return i;
                }
                elemento = elemento->proximo;
            }
            throw ExcecaoDadoInexistente();
        };

        bool contem(T dado) const {
            if(this->_primeiro == nullptr)
                return false;
            if(this->_primeiro->dado == dado){
                return true;
            }
            Elemento<T>* elemento = this->_primeiro->proximo;
            for(std::size_t i = 1; i < this->_tamanho; i++){
                if(elemento->dado == dado){
                    return true;
                }
                elemento = elemento->proximo;
            }
            return false;
        };

        void inserirNoInicio(T dado) {
            Elemento<T>* elemento = new Elemento<T>(dado);
            elemento->proximo = this->_primeiro;
            this->_primeiro = elemento;
            this->_tamanho++;
        };

        void inserir(std::size_t posicao, T dado) {
            if(posicao < 0 || posicao > this->_tamanho)
                throw ExcecaoPosicaoInvalida();

            if(this->_tamanho == 0){
                this->_primeiro = new Elemento<T>(dado, nullptr);
                this->_tamanho++;
            } 
            else if(this->_tamanho != 0 && posicao == 0){
                this->_primeiro = new Elemento<T>(dado, this->_primeiro);
                this->_tamanho++;
            } else {

                Elemento<T>* elemento = this->_primeiro;
                for(std::size_t i = 0; i < posicao -1; i++){
                    elemento = elemento->proximo;
                }
                Elemento<T>* elementoNovo = new Elemento<T>(dado, elemento->proximo);
                elemento->proximo = elementoNovo;
                this->_tamanho++;
            }
        };

        void inserirNoFim(T dado) {
            if(this->_tamanho == 0){
                this->_primeiro = new Elemento<T>(dado, nullptr);
                this->_tamanho++;
                return;
            } 
            Elemento<T>* elementoNovo = new Elemento<T>(dado);
            Elemento<T>* elemento = this->_primeiro;
            for(std::size_t i = 0; i < this->_tamanho - 1; i++){
                elemento = elemento->proximo;
            }
            elemento->proximo = elementoNovo;
            this->_tamanho++;
        };

        T removerDoInicio() {
            if(this->_tamanho == 0)
                throw ExcecaoListaEncadeadaVazia();
            Elemento<T>* elemento = this->_primeiro;
            this->_primeiro = this->_primeiro->proximo;
            T dado = elemento->dado;
            delete elemento;
            this->_tamanho--;
            return dado;
        };

        T removerDe(std::size_t posicao) {
            if(posicao < 0 || posicao >= this->_tamanho)
                throw ExcecaoPosicaoInvalida();

            if(this->_tamanho == 0){
                throw ExcecaoListaEncadeadaVazia();
            } 
            
            if(posicao == 0){
                T dado = this->_primeiro->dado;
                Elemento<T>* elemento = this->_primeiro;
                this->_primeiro = this->_primeiro->proximo;
                delete elemento;
                this->_tamanho--;
                return dado;
            } else{
                Elemento<T>* elemento = this->_primeiro;
                Elemento<T>* elementoProximo = elemento->proximo;
                for(std::size_t i = 0; i < posicao - 1; i++){
                    elemento = elementoProximo;
                    elementoProximo = elementoProximo->proximo;
                }
                if(elementoProximo->proximo != nullptr)
                    elemento->proximo = elementoProximo->proximo;
                else
                    elemento->proximo = nullptr;

                T dado = elementoProximo->dado;
                delete elementoProximo;
                this->_tamanho--;
                return dado;
            }
        };

        T removerDoFim() {
            if(this->_tamanho == 0)
                throw ExcecaoListaEncadeadaVazia();

            Elemento<T>* elemento = this->_primeiro;
            Elemento<T>* elementoUltimo = this->_primeiro->proximo;
            for(std::size_t i = 1; i < this->_tamanho - 1; i++){
                elemento = elementoUltimo->proximo;
                elementoUltimo = elementoUltimo->proximo;
            }
            elemento->proximo = nullptr;
            if(elementoUltimo == nullptr){
                T dado = elemento->dado;
                delete elemento;
                this->_primeiro = nullptr;
                this->_tamanho--;
                return dado;
            }
            else{
                T dado = elementoUltimo->dado;
                delete elementoUltimo;
                this->_tamanho--;
                return dado;
            }
            
        };

        void remover(T dado) {
            if(this->_tamanho == 0)
                throw ExcecaoListaEncadeadaVazia();
            
            if(this->_primeiro->dado == dado){
                removerDoInicio();
                return;
            }

            Elemento<T>* elemento = this->_primeiro;
            for(std::size_t i = 0; i < this->_tamanho; i++){
                if(elemento->dado == dado){
                    removerDe(i);
                    return;
                }
                elemento = elemento->proximo;
            }
            throw ExcecaoDadoInexistente();
        };
};

#endif