#include <stdio.h>
#include <string.h>

struct books
{
  char title[30], author[30];
  int pages, edition, id;
};

void save(struct books *book, int totalBooks, int maxId)
{
  FILE *fp;

  if ((fp = fopen("books.txt", "w+")) == NULL)
  {
    printf("Erro ao salvar!\n");
  }
  else

  {
    fprintf(fp, "%i\n", totalBooks);
    for (int i = 0; i < totalBooks; i++)
    {
      fwrite(&book[i], sizeof(struct books), 1, fp);
    }
    fclose(fp);
  }
}

void load(struct books *book, int *totalBooks, int *maxId)
{
  FILE *fp;

  if ((fp = fopen("books.txt", "r+")) != NULL)
  {
    fscanf(fp, "%i\n", maxId);
    while (fread(&book[*totalBooks], sizeof(struct books), 1, fp) == 1)
    {
      *totalBooks += 1;
    }
    fclose(fp);
  }
}

void create(struct books *book, int *totalBooks, int *maxId)
{
  int registerBooks, length;
  printf("Quantos livros deseja cadastrar? ");
  scanf("%i", &registerBooks);
  length = (*totalBooks);
  for (int i = length; i < registerBooks + length; i++)
  {
    setbuf(stdin, 0);
    printf("\nDados do livro %i\n------------------------------------\n", *totalBooks + 1);
    printf("Digite o titulo: ");
    fgets(book[i].title, 30, stdin);
    printf("Digite o autor: ");
    fgets(book[i].author, 30, stdin);
    printf("Digite a quantidade de paginas: ");
    scanf("%i", &book[i].pages);
    printf("Digite a edicao: ");
    scanf("%i", &book[i].edition);
    printf("------------------------------------\n");
    book[i].id = *maxId + 1;
    book[i].title[strlen(book[i].title) - 1] = '\0';
    book[i].author[strlen(book[i].author) - 1] = '\0';
    *totalBooks += 1;
    *maxId += 1;
  }
}

void delete (struct books *book, int *totalBooks)
{
  int selectedBook, found = 0;
  printf("Digite o codigo do livro a ser removido: ");
  scanf("%i", &selectedBook);
  for (int i = 0; i < *totalBooks; i++)
  {
    if (book[i].id == selectedBook)
    {
      found = 1;
      for (int j = i; j < *totalBooks - 1; j++)
      {
        book[j] = book[j + 1];
      }
    }
  }
  if (found == 1)
  {
    *totalBooks -= 1;
  }
  else
  {
    printf("\nxxxxx Codigo invalido xxxxx\n");
  }
}

void list(struct books *book, int *totalBooks)
{
  for (int i = 0; i < *totalBooks; i++)
  {
    printf("\n\n* Codigo: %i\n* Titulo: %s\n* Autor: %s\n* Qtd paginas: %i\n* Edicao: %i\n", book[i].id, book[i].title, book[i].author, book[i].pages, book[i].edition);
    printf("\n------------------------------------------------\n");
  }
}

void searchById(struct books *book, int *totalBooks)
{
  int selectedBook, found = 0;
  printf("Digite o codigo do livro para consulta: ");
  scanf("%i", &selectedBook);
  for (int i = 0; i < *totalBooks; i++)
  {
    if (book[i].id == selectedBook)
    {
      found = 1;
      printf("\n\n* Codigo: %i\n* Titulo: %s\n* Autor: %s\n* Qtd paginas: %i\n* Edicao: %i\n", book[i].id, book[i].title, book[i].author, book[i].pages, book[i].edition);
      printf("\n------------------------------------------------\n");
    }
  }
  if (found == 0)
  {
    printf("\nxxxxx Livro inexistente xxxxx\n");
  }
}

void searchByPages(struct books *book, int *totalBooks)
{
  int selectedBook;
  printf("Digite a quantidade de paginas para consulta: ");
  scanf("%d", &selectedBook);
  for (int i = 0; i < *totalBooks; i++)
  {
    if (book[i].pages == selectedBook)
    {
      printf("\n\n* Codigo: %i\n* Titulo: %s\n* Autor: %s\n* Qtd paginas: %i\n* Edicao: %i\n", book[i].id, book[i].title, book[i].author, book[i].pages, book[i].edition);
      printf("\n------------------------------------------------\n");
    }
  }
}

void updateEdition(struct books *book, int *totalBooks)
{
  int selectedBook, newEdition;
  printf("Digite o codigo do livro que deseja atualizar a edicao: ");
  scanf("%i", &selectedBook);
  for (int i = 0; i < *totalBooks; i++)
  {
    if (selectedBook == book[i].id)
    {
      printf("\n\n* Codigo: %i\n* Titulo: %s\n* Autor: %s\n* Qtd paginas: %i\n* Edicao: %i\n", book[i].id, book[i].title, book[i].author, book[i].pages, book[i].edition);
      printf("\n------------------------------------------------\n");

      printf("\nQual sera a nova edicao? ");
      scanf("%i", &newEdition);
      book[i].edition = newEdition;

      printf("\n\n-------- Livro atualizado --------\n\n");

      printf("\n\n* Codigo: %i\n* Titulo: %s\n* Autor: %s\n* Qtd paginas: %i\n* Edicao: %i\n", book[i].id, book[i].title, book[i].author, book[i].pages, book[i].edition);
      printf("\n------------------------------------------------\n");
    }
  }
}

int main()
{
  struct books book[50];
  int option, totalBooks = 0, maxId = 0;

  load(book, &totalBooks, &maxId);

  do
  {
    printf("\nDigite 1 para cadastrar um novo livro\nDigite 2 para remover um livro\nDigite 3 para listar todos os livros\nDigite 4 para consultar um livro pelo codigo\nDigite 5 para consultar um livro pela quantidade de paginas\nDigite 6 para atualizar a edicao de um livro\nDigite 7 para sair\n\n");
    printf("Resposta: ");
    scanf("%i", &option);
    switch (option)
    {
    case 1:
      create(book, &totalBooks, &maxId);
      save(book, totalBooks, maxId);
      break;
    case 2:
      delete (book, &totalBooks);
      save(book, totalBooks, maxId);
      break;
    case 3:
      list(book, &totalBooks);
      break;
    case 4:
      searchById(book, &totalBooks);
      break;
    case 5:
      searchByPages(book, &totalBooks);
      break;
    case 6:
      updateEdition(book, &totalBooks);
      save(book, totalBooks, maxId);
      break;
    case 7:
      printf("\nAte logo!\n");
      break;
    default:
      printf("\nxxxxxx Opcao invalida xxxxxx\n");
      break;
    }
  } while (option != 7);
}