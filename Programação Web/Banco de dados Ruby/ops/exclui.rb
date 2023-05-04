$:.push './'
require_relative '../ar.rb'

# Funcao que insere nas tabelas
def exclui(words, nomeTabela)

    if (nomeTabela == "doctors" || nomeTabela == "hospitals" || nomeTabela == "bosses" || nomeTabela == "rooms")

        # cria uma hash para armazenar as condicoes
        conditions = {};

        # checa se o usuario digitou as condicoes4
        if (words.length > 2)

                for i in 2...words.length

                    # Divide entre atributo e valor
                    attribute, value = words[i].split("=", 2);

                    # tira as aspas adicionais ao adicionar na hash para ficar certinho
                    value = value.gsub(/"/, "");

                    # Guarda os atributos com seus valores na hash
                    conditions[attribute.to_sym] = value;
                end

            # Passa as condicoes como parametros para delecao
            if (nomeTabela == "doctors")
                Doctor.where(conditions).destroy_all;
            elsif (nomeTabela == "hospitals")
                Hospital.where(conditions).destroy_all;
            elsif (nomeTabela == "bosses")
                Boss.where(conditions).destroy_all;
            elsif (nomeTabela == "rooms")
                Room.where(conditions).destroy_all;
            end
        end
    end
end
