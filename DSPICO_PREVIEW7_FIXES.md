# DSPico Launcher — correções da lista de banners

Alterações desta revisão:

1. A primeira linha do banner passa a usar alinhamento central nos temas Material e Custom.
2. `Label3DView` passa a aplicar alinhamento horizontal, que antes era ignorado pelos temas personalizados.
3. O texto atual é reenviado à VRAM logo depois da alocação da textura. Isso corrige o caso em que uma linha ficava invisível até o item receber foco.

## Arquivos alterados

- `arm9/source/gui/views/Label3DView.cpp`
- `arm9/source/romBrowser/Theme/custom/CustomBannerListItemView.cpp`
- `arm9/source/romBrowser/Theme/Material/MaterialBannerListItemView.cpp`

## Validação

O código foi revisado estruturalmente, mas não foi compilado neste ambiente com BlocksDS e ainda não foi testado em um Nintendo DS. Compile pelo mesmo GitHub Actions que já funcionou para o projeto e teste primeiro em uma cópia do cartão SD.
