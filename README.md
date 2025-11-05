# Proyecto Compiladores 2

Bienvenido/a a *Proyecto Compiladores 2*. Este repositorio contiene el código, la documentación y los recursos asociados a un proyecto educativo de compiladores. El README está escrito en español y está pensado para usarse como punto de partida; ajusta las secciones concretas (lenguaje, comandos, rutas) según la implementación real del proyecto.

## Descripción

Proyecto Compiladores 2 es un trabajo práctico de compiladores cuyo objetivo es diseñar e implementar las fases principales de un compilador: análisis léxico, análisis sintáctico, análisis semántico, generación/intermedia y, opcionalmente, generación de código/optimización. El proyecto puede incluir un lenguaje de dominio pequeño (mini-lenguaje) para demostrar las capacidades del compilador.

## Características

- Analizador léxico (tokenizador) con manejo de comentarios y literales.
- Analizador sintáctico (por ejemplo, LL(1) o LR) que construye un AST.
- Análisis semántico: tablas de símbolos, chequeo de tipos y validaciones.
- Generación de código intermedio (tac/3-address code) y/o generación de código objetivo (opcional).
- Conjunto de pruebas de ejemplo y programas de prueba.

## Requisitos (asunciones)

Asumo que el proyecto está implementado en un lenguaje moderno (por ejemplo Python, Java, C# o OCaml). Ajusta estas instrucciones si usas otro lenguaje.

- Python 3.8+ (si la implementación es en Python) o JDK 11+ (si en Java).
- Herramientas de build según lenguaje (pip, virtualenv, Maven, Gradle, dotnet, etc.).

## Estructura sugerida de carpetas

- src/                - Código fuente del compilador
- tests/              - Tests unitarios y de integración
- examples/           - Programas de ejemplo (entradas de prueba)
- docs/               - Documentación adicional (gramática, diagramas)
- build/              - Artefactos de compilación y salidas intermedias
- README.md           - Este archivo


## Instalación (ejemplos)

Si el proyecto es en Python (ejemplo):

```powershell
# crear y activar entorno virtual (Windows PowerShell)
python -m venv .venv; .\.venv\Scripts\Activate.ps1
pip install -r requirements.txt
```

Si el proyecto es en Java (ejemplo con Maven):

```powershell
mvn clean install
```

Ajusta los comandos anteriores al lenguaje y a la herramienta de build que uses.

## Uso

Ejecuta el compilador sobre un archivo fuente de ejemplo. Ejemplos genéricos:

Python (suponiendo un script `compile.py`):

```powershell
# analizar y compilar un archivo de ejemplo
python src\compile.py examples\programa_ejemplo.lang -o build\programa_ejemplo.out
```

Java (suponiendo una clase Main empaquetada):

```powershell
java -jar target\proyecto-compiladores-2.jar examples\programa_ejemplo.lang
```

Incluye en el proyecto scripts concretos (`run`, `build`, `test`) que simplifiquen estos pasos.

## Tests

Añade tests unitarios para el analizador léxico, sintáctico y semántico. Ejemplos de ejecución (Python/pytest):

```powershell
# ejecutar tests
pytest -q
```

## Cómo contribuir

1. Haz fork del repositorio.
2. Crea una rama con una descripción clara: `feature/mi-mejora` o `fix/eror-x`.
3. Abre un Pull Request explicando los cambios.
4. Añade tests para cualquier funcionalidad nueva o corrección.

## Buenas prácticas y recomendaciones

- Mantén la gramática y la especificación del lenguaje en `docs/` (BNF/EBNF).
- Versiona los casos de prueba en `examples/` y documenta su propósito.
- Separa claramente las fases del compilador en módulos para facilitar pruebas unitarias.

## Licencia

Añade aquí la licencia que corresponde (por ejemplo MIT, GPL, CC). Si no has decidido, puedes usar MIT como plantilla.

## Contacto

Si querés más cambios en el README o que lo adapte a un lenguaje/estructura concreta, decime cuál es la implementación (p. ej. Python, Java, OCaml) y lo ajusto.

---

Archivo generado automáticamente: si querés, puedo añadir badges (build/tests) o crear scripts `run` y `test` en el repo.
