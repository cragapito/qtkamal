# QtKamal

Ferramenta auxiliar para Radiodeterminação.

Este software tem por objetivo auxiliar na localização de fontes emissoras de radiofrequência, não substitui os métodos convencionais ou qualquer sistema existente, não existem quaisquer garantias, expressas ou implícitas, de qualquer natureza, em especial sobre a exatidão e o uso que se possa ser feito das informações calculadas ou geradas por ele.

Escrito por Cleyton Ricardo Agapito <cragapito@gmail.com>. Iniciado na [Anatel](https://www.anatel.gov.br) em 2013.

## Definições

**kamal** foi inspirado em um instrumento rústico de navegação utilizado pelos árabes no final do século IX, trata-se de uma corda com nós presa a um retângulo de madeira. Maiores informações em [Wikipédia - Kamal (navigation)](http://en.wikipedia.org/wiki/Kamal_(navigation)).

**Qt** é uma tecnologia de desenvolvimento de interfaces gráficas desenvolvidas pela Trooltech®, tadicionalmente programas que usam esta tecnologia mantém este prefixo. Maiores informações em [The Qt Project](http://qt-project.org).

**KML** é um padrão oficialmente conhecido como OpenGIS® KML Encoding Standard (OGC KML), mantido pelo Open Geospatial Consortium, Inc. (OGC), a especificação completa pode ser obtida em [http://www.opengeospatial.org/standards/kml](http://www.opengeospatial.org/standards/kml), o schema XML completo pode ser obtido em [http://schemas.opengis.net/kml)](http://schemas.opengis.net/kml). 

**KMZ** é a versão compacta do **KML**. (Depende da disponibilidade da biblioteca [QuaZIP](https://quazip.sourceforge.net)).

## Documentação

A documentação completa está em /doc.

## Recomendações

As fórmulas utilizadas baseiam-se na aproximação esférica da terra com raio de **6.378,137 km** (padrão [WGS-84](https://pt.wikipedia.org/wiki/WGS84)) ignorando distorções da geóide, erro típico do método na ordem de **0,3%**.

A interface foi desenhada visando a agilidade na entrada e transformação de dados (com decimal de segundos com uma casa), as alterações são imediatamente escritas no arquivo em uso (o que tem o nome ao lado do globo azul, no topo do quadro interno à janela). Existe uma pequena possibilidade de perda de dados, portanto não esqueça de fazer uma cópia de segurança caso precise resgatar o arquivo original.

Caso seja inserido algum elemento pelos botões que contém um "+" sem carregar nenhum arquivo antes, será apresentado um diálogo solicitando o nome do arquivo de destino, que pode conter a extensão do formato de saída desejado, ou apenas o nome para a geração do formato padrão (.kmz). (Depende da disponibilidade da biblioteca [QuaZIP](https://quazip.sourceforge.net)).

Abrindo um novo arquivo após outro já ter sido aberto fará com que os dados do arquivo antigo fiquem obsoletos (na cor cinza), um duplo click o rehabilitará e trará os dados para o arquivo de trabalho atual. Para removê-los da tela use o botão direito 'limpa obsoletos'. Caso não sejam rehabilitados, serão automaticamente excluídos.

Arquivos **KML** ou **KMZ** podem ser arrastados para a interface, para o executável ou serem indicados na linha de comando. (**KMZ** depende da disponibilidade da biblioteca [QuaZIP](https://quazip.sourceforge.net)).

As alterações no arquivo são as mínimas possíveis, ele deve ser capaz de reconhecer ícones de pontos acrescentadas ou alteradas por um browser terrestre como o GoogleEarth®. Os itens podem ser promovidos e demovidos, ou seja, arrastados para outro grupo (Ponto, Feixe ou Área), e neste caso serão redefinidos para estilos pré-formatados. Podem também ser copiados segurando-se a tecla <Ctrl> enquando são arrastados.

Os itens de área são aproximações para polígonos e podem conter erros de posicionamento (quanto mais pontos, menores os erros). A definição do polígono é sempre recalculada, alterações neste polígono feitas fora do programa serão sobreescritas.

## Licença e Termos de uso

A Licença está sob os termos da [BSD 3-Clause](https://opensource.org/license/bsd-3-clause), a mais livre e abrangente possível. Resumindo, pode fechar e vender, desde que mantenha o nome dos autores.

Licenças mais restritivas podem ser aplicadas dependendo do fornecedor, mas é possível excluí-las por diretivas de compilação, mantendo o núcleo do projeto.

## Referências externas

* [http://en.wikipedia.org/wiki/Kamal_(navigation)](http://en.wikipedia.org/wiki/Kamal_(navigation))
* [http://qt-project.org](http://qt-project.org)
* [http://www.opengeospatial.org/standards/kml](http://www.opengeospatial.org/standards/kml)
* [http://schemas.opengis.net/kml](http://schemas.opengis.net/kml)
* [https://quazip.sourceforge.net](https://quazip.sourceforge.net)
* [http://pt.wikipedia.org/wiki/Fórmula_de_Haversine](http://pt.wikipedia.org/wiki/Fórmula_de_Haversine)
* [http://pt.wikipedia.org/wiki/Mercator](http://pt.wikipedia.org/wiki/Mercator)
