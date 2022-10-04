#ifndef MINHAARVOREDEBUSCABINARIA_H
#define MINHAARVOREDEBUSCABINARIA_H

#include "ArvoreDeBuscaBinaria.h"
#include <cassert>
#include <utility>
#include <algorithm>

/**
 * @brief Representa uma árvore binária de busca.
 * 
 * @tparam T O tipo de dado guardado na árvore.
 */
template<typename T>
class MinhaArvoreDeBuscaBinaria : public ArvoreDeBuscaBinaria<T>
{
    //implemente aqui
    public:
    ~MinhaArvoreDeBuscaBinaria<T>(){
        destrutor(this->_raiz);
    }

    protected:
        void destrutor(Nodo<T>* nodo){
            if(nodo == nullptr)
                return;
            destrutor(nodo->filhoDireita);
            destrutor(nodo->filhoEsquerda);

            delete nodo;
        };

        int verificaChave(Nodo<T>* nodo) const {
            if(nodo == nullptr)
                return 0;

            return 1 + verificaChave(nodo->filhoEsquerda) + verificaChave(nodo->filhoDireita);
        };

        Nodo<T>* achaNodoporChave(Nodo<T>* nodo, T chave) const{
            if(nodo == nullptr)
                return nullptr;
            if(nodo->chave == chave)
                return nodo;
            
            if(chave > nodo->chave)
                return achaNodoporChave(nodo->filhoDireita, chave);
            else
                return achaNodoporChave(nodo->filhoEsquerda, chave);
        };
        

        int achaAltura(Nodo<T>* nodo) const{
            if(nodo == nullptr)
                return -1;
            int alturaEsquerda = achaAltura(nodo->filhoEsquerda);
            int alturaDireita = achaAltura(nodo->filhoDireita);
            return 1 + (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita);
        }

        bool contemRecursivo(Nodo<T>* nodo, T chave) const{
            if(nodo == nullptr)
                return false;

            if(nodo->chave == chave){
                return true;
            } else
            if(chave > nodo->chave){
                return contemRecursivo(nodo->filhoDireita, chave);
            } else{
                return contemRecursivo(nodo->filhoEsquerda, chave);
            }
            return false;
        };

        void inserirRecursivo(Nodo<T>* nodo, T chave) const{
            if(chave >= nodo->chave){
                if(nodo->filhoDireita == nullptr){
                    Nodo<T>* nodoNovo = new Nodo<T>;
                    nodoNovo->chave = chave;
                    nodo->filhoDireita = nodoNovo;
                    nodo->altura = achaAltura(nodo);
                    return;
                } else{
                    inserirRecursivo(nodo->filhoDireita, chave);                    
                    nodo->altura = achaAltura(nodo);
                    return;
                }
            } else{
                if(nodo->filhoEsquerda == nullptr){
                    Nodo<T>* nodoNovo = new Nodo<T>;
                    nodoNovo->chave = chave;
                    nodo->filhoEsquerda = nodoNovo;
                    nodo->altura = achaAltura(nodo);
                    return;
                } else{
                    inserirRecursivo(nodo->filhoEsquerda, chave);
                    nodo->altura = achaAltura(nodo);
                    return;
                }
            }
        }

        Nodo<T>* achaNodoPai(Nodo<T>* nodo, T chave) const{
            if(nodo->filhoEsquerda == nullptr && nodo->filhoDireita == nullptr)
                return nullptr;

            if(nodo->filhoEsquerda->chave == chave || nodo->filhoDireita->chave == chave)
                return nodo;
            
            if(chave > nodo->chave){
                return achaNodoPai(nodo->filhoDireita, chave);
            } else{
                return achaNodoPai(nodo->filhoEsquerda, chave);
            }
        };

        Nodo<T>* achaMenorDireita(Nodo<T>* nodo){
            if(nodo->filhoEsquerda == nullptr){
                return nodo;
            }

            return achaMenorDireita(nodo->filhoEsquerda);
        }

        void criaListaEm(Nodo<T>* nodo, ListaEncadeadaAbstrata<T>* lista) const{
            if(nodo!= nullptr){
                criaListaEm(nodo->filhoEsquerda, lista);
                lista->inserirNoFim(nodo->chave);
                criaListaEm(nodo->filhoDireita, lista);
            }
            return;
        }

        void criaListaPre(Nodo<T>* nodo, ListaEncadeadaAbstrata<T>* lista) const{
            if(nodo!= nullptr){
                lista->inserirNoFim(nodo->chave);
                criaListaPre(nodo->filhoEsquerda, lista);
                criaListaPre(nodo->filhoDireita, lista);
            }
            return;
        }

        void criaListaPos(Nodo<T>* nodo, ListaEncadeadaAbstrata<T>* lista) const{
            if(nodo!= nullptr){
                criaListaPos(nodo->filhoEsquerda, lista);
                criaListaPos(nodo->filhoDireita, lista);
                lista->inserirNoFim(nodo->chave);
            }
            return;
        }

        int atualizaAlturas(Nodo<T>* nodo){
            if(nodo == nullptr)
                return -1; 

            int alturaEsquerda = atualizaAlturas(nodo->filhoEsquerda);
            int alturaDireita = atualizaAlturas(nodo->filhoDireita);
            nodo->altura = std::max(alturaEsquerda, alturaDireita) + 1;
            return nodo->altura;
        }

    public:
        bool vazia() const{
            if(this->_raiz == nullptr)
                return true;
            else 
                return false;
        };

        int quantidade() const{
            return verificaChave(this->_raiz);
        };

        bool contem(T chave) const{
            if(this->_raiz == nullptr)
                return false;

            if(chave == this->_raiz->chave){
                return true;
            } else if(chave > this->_raiz->chave){
                return contemRecursivo(this->_raiz->filhoDireita, chave);
            } else{
                return contemRecursivo(this->_raiz->filhoEsquerda, chave);
            } 
            return false;
        };

        std::optional<int> altura(T chave) const{
            Nodo<T>* nodo = achaNodoporChave(this->_raiz, chave);
            if(nodo == nullptr)
                return std::nullopt;
            
            //max(altura do filho da esquerda, altura do filho a direita)
            //altura dos null é -1
            return nodo->altura;
        };

        void inserir(T chave){
            if(this->_raiz == nullptr){
                this->_raiz = new Nodo<T>;
                this->_raiz->chave = chave;
                return;
            }
            inserirRecursivo(this->_raiz, chave);
        };

        void remover(T chave){
            Nodo<T>* nodo = achaNodoporChave(this->_raiz, chave);
            Nodo<T>* nodoPai = achaNodoPai(this->_raiz, chave);
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
                Nodo<T>* nodoTmp = achaMenorDireita(nodo->filhoDireita);
                Nodo<T>* nodoPaiTmp = achaNodoPai(this->_raiz, nodoTmp->chave);
                if(nodo == this->_raiz){
                    this->_raiz = nodoTmp;
                    this->_raiz->filhoEsquerda = nodo->filhoEsquerda;
                    this->_raiz->filhoDireita = nodo->filhoDireita;
                } else if(nodo->chave > nodoPai->chave){
                    nodoPai->filhoDireita = nodoTmp;
                    //nodoPai->altura = achaAltura(nodoPai);
                }else {
                    nodoPai->filhoEsquerda = nodoTmp;
                    //nodoPai->altura = achaAltura(nodoPai);
                }
                nodoPaiTmp->filhoEsquerda = nullptr;
                //nodoTmp->altura = achaAltura(nodoTmp);
                nodoTmp->filhoEsquerda = nodo->filhoEsquerda;
                nodoTmp->filhoDireita = nodo->filhoDireita;
                delete nodo;
            }
            atualizaAlturas(this->_raiz);
        };

        std::optional<T> filhoEsquerdaDe(T chave) const{
            Nodo<T>* nodo = achaNodoporChave(this->_raiz, chave);
            if(nodo == nullptr || nodo->filhoEsquerda == nullptr)
                return std::nullopt;

            return nodo->filhoEsquerda->chave;
        };

        std::optional<T> filhoDireitaDe(T chave) const{
            Nodo<T>* nodo = achaNodoporChave(this->_raiz, chave);
            if(nodo == nullptr || nodo->filhoDireita == nullptr)
                return std::nullopt;

            return nodo->filhoDireita->chave;
        };

        ListaEncadeadaAbstrata<T>* emOrdem() const{
            ListaEncadeadaAbstrata<T>* lista = new MinhaListaEncadeada<T>;
            if(this->_raiz != nullptr)
                criaListaEm(this->_raiz, lista);
            
            return lista;
        };

        ListaEncadeadaAbstrata<T>* preOrdem() const{
            ListaEncadeadaAbstrata<T>* lista = new MinhaListaEncadeada<T>;
            if(this->_raiz != nullptr)
                criaListaPre(this->_raiz, lista);
            
            return lista;
        };

        ListaEncadeadaAbstrata<T>* posOrdem() const{
            ListaEncadeadaAbstrata<T>* lista = new MinhaListaEncadeada<T>;
            if(this->_raiz != nullptr)
                criaListaPos(this->_raiz, lista);
            
            return lista;
        };
};

#endif
