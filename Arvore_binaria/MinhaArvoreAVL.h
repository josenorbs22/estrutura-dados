#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "MinhaArvoreDeBuscaBinaria.h"

/**
 * @brief Representa uma árvore AVL.
 * 
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public MinhaArvoreDeBuscaBinaria<T>
{
    //implemente aqui
    /* public: 
        MinhaArvoreAVL<T>(){};
        ~MinhaArvoreAVL<T>(){}; */
    private:
        void verificaBalanceamento(Nodo<T>* nodo){
            if(nodo == nullptr || (nodo->filhoEsquerda == nullptr && nodo->filhoDireita == nullptr))
                return;
            int alturaEsquerda, alturaDireita;
            if(nodo->filhoEsquerda == nullptr)
                alturaEsquerda = -1;
            else 
                alturaEsquerda = nodo->filhoEsquerda->altura;

            if(nodo->filhoDireita == nullptr)
                alturaDireita = -1;
            else 
                alturaDireita = nodo->filhoDireita->altura;

            int b = alturaEsquerda - alturaDireita;
            if(b > 1 || b < -1){
                if(b > 0){
                    if(nodo->filhoEsquerda->filhoEsquerda == nullptr)
                        alturaEsquerda = -1;
                    else 
                        alturaEsquerda = nodo->filhoEsquerda->filhoEsquerda->altura;

                    if(nodo->filhoEsquerda->filhoDireita == nullptr)
                        alturaDireita = -1;
                    else 
                        alturaDireita = nodo->filhoEsquerda->filhoDireita->altura;

                    b = alturaEsquerda - alturaDireita;

                    if(b >= 0){
                        rotacaoSimplesDireita(nodo);
                    } else{
                        rotacaoEsquerdaDireita(nodo);
                    }
                } else{
                    if(nodo->filhoDireita->filhoEsquerda == nullptr)
                        alturaEsquerda = -1;
                    else 
                        alturaEsquerda = nodo->filhoDireita->filhoEsquerda->altura;

                    if(nodo->filhoDireita->filhoDireita == nullptr)
                        alturaDireita = -1;
                    else 
                        alturaDireita = nodo->filhoDireita->filhoDireita->altura;

                    b = alturaEsquerda - alturaDireita;

                    if(b <= 0){
                        rotacaoSimplesEsquerda(nodo);
                    } else{
                        rotacaoDireitaEsquerda(nodo);
                    }
                }
            } 
        };

        void rotacaoSimplesDireita(Nodo<T>* nodo){
            Nodo<T>* tmp = nodo->filhoEsquerda;
            
            nodo->filhoEsquerda = tmp->filhoDireita;
            tmp->filhoDireita = nodo;
            tmp->filhoDireita->altura = MinhaArvoreDeBuscaBinaria<T>::achaAltura(tmp->filhoDireita);
            tmp->filhoEsquerda->altura = MinhaArvoreDeBuscaBinaria<T>::achaAltura(tmp->filhoEsquerda);
            tmp->altura = MinhaArvoreDeBuscaBinaria<T>::achaAltura(tmp);
            
            if(nodo == this->_raiz){
                this->_raiz = tmp;
                this->_raiz->filhoDireita->altura = MinhaArvoreDeBuscaBinaria<T>::achaAltura(this->_raiz->filhoDireita);
            } else{
                Nodo<T>* nodoPai = MinhaArvoreDeBuscaBinaria<T>::achaNodoPai(this->_raiz, nodo->chave);
                nodoPai->filhoEsquerda = tmp;
            }
        }

        void rotacaoSimplesEsquerda(Nodo<T>* nodo){
            Nodo<T>* tmp = nodo->filhoDireita;
            nodo->filhoDireita = tmp->filhoEsquerda;
            tmp->filhoEsquerda = nodo;
            tmp->filhoDireita->altura = MinhaArvoreDeBuscaBinaria<T>::achaAltura(tmp->filhoDireita);
            tmp->filhoEsquerda->altura = MinhaArvoreDeBuscaBinaria<T>::achaAltura(tmp->filhoEsquerda);
            tmp->altura = MinhaArvoreDeBuscaBinaria<T>::achaAltura(tmp);

            if(nodo == this->_raiz){
                this->_raiz = tmp;
                this->_raiz->filhoEsquerda->altura = MinhaArvoreDeBuscaBinaria<T>::achaAltura(this->_raiz->filhoEsquerda);
            } else{
                Nodo<T>* nodoPai = MinhaArvoreDeBuscaBinaria<T>::achaNodoPai(this->_raiz, nodo->chave);
                nodoPai->filhoDireita = tmp;
            }
        }

        void rotacaoEsquerdaDireita(Nodo<T>* nodo){
            Nodo<T>* tmp = nodo->filhoEsquerda->filhoDireita;
            nodo->filhoEsquerda->filhoDireita = nodo->filhoEsquerda->filhoDireita->filhoEsquerda;
            tmp->filhoEsquerda = nodo->filhoEsquerda;
            nodo->filhoEsquerda = nullptr;
            tmp->filhoDireita = nodo;
            tmp->filhoDireita->altura = MinhaArvoreDeBuscaBinaria<T>::achaAltura(tmp->filhoDireita);
            tmp->filhoEsquerda->altura = MinhaArvoreDeBuscaBinaria<T>::achaAltura(tmp->filhoEsquerda);
            tmp->altura = MinhaArvoreDeBuscaBinaria<T>::achaAltura(tmp);

            if(nodo == this->_raiz){
                this->_raiz = tmp;
                this->_raiz->filhoDireita->altura = MinhaArvoreDeBuscaBinaria<T>::achaAltura(this->_raiz->filhoDireita);
            } else{
                Nodo<T>* nodoPai = MinhaArvoreDeBuscaBinaria<T>::achaNodoPai(this->_raiz, nodo->chave);
                nodoPai->filhoEsquerda = tmp;
            }
        }

        void rotacaoDireitaEsquerda(Nodo<T>* nodo){
            Nodo<T>* tmp = nodo->filhoDireita->filhoEsquerda;
            nodo->filhoDireita->filhoEsquerda = nodo->filhoDireita->filhoEsquerda->filhoDireita;
            tmp->filhoDireita = nodo->filhoDireita;
            nodo->filhoDireita = nullptr;
            tmp->filhoEsquerda = nodo;
            tmp->filhoDireita->altura = MinhaArvoreDeBuscaBinaria<T>::achaAltura(tmp->filhoDireita);
            tmp->filhoEsquerda->altura = MinhaArvoreDeBuscaBinaria<T>::achaAltura(tmp->filhoEsquerda);
            tmp->altura = MinhaArvoreDeBuscaBinaria<T>::achaAltura(tmp);

            if(nodo == this->_raiz){
                this->_raiz = tmp;
                this->_raiz->filhoEsquerda->altura = MinhaArvoreDeBuscaBinaria<T>::achaAltura(this->_raiz->filhoEsquerda);
            } else{
                Nodo<T>* nodoPai = MinhaArvoreDeBuscaBinaria<T>::achaNodoPai(this->_raiz, nodo->chave);
                nodoPai->filhoDireita = tmp;
            } 
        }

        void inserirRecursivo(Nodo<T>* nodo, T chave){
            if(chave >= nodo->chave){
                if(nodo->filhoDireita == nullptr){
                    Nodo<T>* nodoNovo = new Nodo<T>;
                    nodoNovo->chave = chave;
                    nodo->filhoDireita = nodoNovo;
                    nodo->altura = MinhaArvoreDeBuscaBinaria<T>::achaAltura(nodo);                   
                    return;
                } else{
                    inserirRecursivo(nodo->filhoDireita, chave);                    
                    nodo->altura = MinhaArvoreDeBuscaBinaria<T>::achaAltura(nodo);
                    verificaBalanceamento(nodo);
                    return;
                }
            } else{
                if(nodo->filhoEsquerda == nullptr){
                    Nodo<T>* nodoNovo = new Nodo<T>;
                    nodoNovo->chave = chave;
                    nodo->filhoEsquerda = nodoNovo;
                    nodo->altura = MinhaArvoreDeBuscaBinaria<T>::achaAltura(nodo);
                    return;
                } else{
                    inserirRecursivo(nodo->filhoEsquerda, chave);
                    nodo->altura = MinhaArvoreDeBuscaBinaria<T>::achaAltura(nodo);
                    verificaBalanceamento(nodo);
                    return;
                }
            }
        }

  public:
        void inserir(T chave){
            if(this->_raiz == nullptr){
                this->_raiz = new Nodo<T>;
                this->_raiz->chave = chave;
                return;
            }
            inserirRecursivo(this->_raiz, chave);
            //verificaBalanceamento(this->_raiz);
        }

        void remover(T chave){
            Nodo<T>* nodo = MinhaArvoreDeBuscaBinaria<T>::achaNodoporChave(this->_raiz, chave);
            Nodo<T>* nodoPai = MinhaArvoreDeBuscaBinaria<T>::achaNodoPai(this->_raiz, chave);
            if(nodo == nullptr)
                return;

            if(nodo->filhoDireita == nullptr && nodo->filhoEsquerda == nullptr){
                if(nodo == this->_raiz)
                    this->_raiz = nullptr;
                else if(nodoPai->filhoEsquerda == nodo){
                    nodoPai->filhoEsquerda = nullptr;
                } else{
                    nodoPai->filhoDireita = nullptr;
                }
                delete nodo;
                
            } else if(nodo->filhoEsquerda != nullptr && nodo->filhoDireita == nullptr){
                nodoPai->filhoEsquerda = nodo->filhoEsquerda;
                delete nodo;
            } else if(nodo->filhoDireita != nullptr && nodo->filhoEsquerda->filhoEsquerda == nullptr){
                if(nodo != this->_raiz)
                    nodoPai->filhoEsquerda = nodo->filhoDireita;
                nodo->filhoDireita->filhoEsquerda = nodo->filhoEsquerda;
                if(this->_raiz == nodo){
                    this->_raiz = nodo->filhoDireita;
                }
                delete nodo;
            } else {
                Nodo<T>* nodoTmp = MinhaArvoreDeBuscaBinaria<T>::achaMenorDireita(nodo->filhoDireita);
                Nodo<T>* nodoPaiTmp = MinhaArvoreDeBuscaBinaria<T>::achaNodoPai(this->_raiz, nodoTmp->chave);
                if(nodo == this->_raiz){
                    this->_raiz = nodoTmp;
                    this->_raiz->filhoEsquerda = nodo->filhoEsquerda;
                    this->_raiz->filhoDireita = nodo->filhoDireita;
                } else if(nodo->chave > nodoPai->chave){
                    nodoPai->filhoDireita = nodoTmp;
                }else {
                    nodoPai->filhoEsquerda = nodoTmp;
                }
                nodoPaiTmp->filhoEsquerda = nullptr;
                nodoTmp->filhoEsquerda = nodo->filhoEsquerda;
                nodoTmp->filhoDireita = nodo->filhoDireita;
                delete nodo;
                verificaBalanceamento(nodoPaiTmp);
            }
            MinhaArvoreDeBuscaBinaria<T>::atualizaAlturas(this->_raiz);
            verificaBalanceamento(nodoPai);
        };
};

#endif