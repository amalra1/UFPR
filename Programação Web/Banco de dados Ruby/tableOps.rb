$:.push './'
require_relative 'ar.rb'
require_relative 'ops/lista.rb'
require_relative 'ops/insere.rb'
require_relative 'ops/exclui.rb'
require_relative 'ops/altera.rb'
require_relative 'ops/info.rb'

# Funcao que extrai o valor do atributo
def extrai_valor_atributo(input, nomeAtributo)

    index = input.index(nomeAtributo);

    # Se o usuario digitou o nome do atributo
    if (index)
    
	# Para pular para o valor do atributo, se foi achado
        index = index + nomeAtributo.length;
	value = input.slice(index, input.length - index).split('"').second;
    end

    # Retorna o valor do atributo
    value;
end
        
  
print "\nBem vindo ao gerenciador do banco de dados\n\n";
print "Comandos funcionam desta maneira:\n< operacao > < tabela > { atributo=\"valor\" } { atributo=... } ...\n"
print "Operacoes disponiveis --> 'lista', 'insere', 'exclui', 'altera, 'info' e 'exit'\n";
print "Tabelas disponiveis --> 'doctors', 'bosses', 'rooms' e 'hospitals'.\n\n";
print "OBS: eh necessario preencher todos os atributos de uma tabela para a validacao ser concluida\n";
print "Digite 'info' para o painela de ajuda.\n\n"

# Le entrada do usuario
input = gets;

# Separa a entrada em um vetor de palavras, o delimitador é o " "
# porem, o que esta entre aspas nao eh separado internamente
# por isso, utilizo o metodo scan ao inves de split
input = input.force_encoding('UTF-8');
words = input.scan(/(?:[^\s"]+|"[^"]*")+/);


while (words[0] != "exit")

    # Trata a operacao
    if (words[0] == "lista")

        lista(words[1]);

    elsif (words[0] == "insere")

        insere(input, words[1]);

    elsif (words[0] == "exclui")

        exclui(words, words[1]);

    elsif (words[0] == "altera")
 
        altera(words, words[1]);

    elsif (words[0] == "info")

        info();

    elsif (words[0] == "exit")
        
	puts "Fechando programa.";
        break;	    

    else
    
        puts "Operacao desconhecida.\n";
    end

    input = gets;
    input = input.force_encoding('UTF-8');
    words = input.scan(/(?:[^\s"]+|"[^"]*")+/);
end

if (words[0] == "exit")

    puts "Fechando programa.";
end
