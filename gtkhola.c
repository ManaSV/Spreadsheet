#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

enum tipo{ FILA, COLUMNA };

static void button_clicked( GtkWidget* widget, gpointer data );
void set_label_number( gchar** string, int x );
void set_guide( GtkWidget** button, gchar** label, GtkWidget* grid, int lim, int flag );
GtkWidget*** set_cells( int x, int y, gchar*** content );
void fill_grid( GtkWidget*** celda, gchar*** content, GtkWidget* grid, GtkWidget* window ,int x, int y );

int main (int argc, char *argv[]) {
	gtk_init (&argc, &argv);
	gint x, y;
	printf( "INGRESE NUMERO DE COLUMNAS: " );
	scanf( "%d", &x );
	printf( "INGRESE NUMERO DE FILAS: " );
	scanf( "%d", &y );
	GtkWidget* window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	GtkWidget* grid = gtk_grid_new();
	gchar** x_label = malloc( sizeof( gchar* ) * x );
	gchar** y_label = malloc( sizeof( gchar* ) * y );
	GtkWidget** buttonx = malloc( sizeof( GtkWidget* ) * x );
	GtkWidget** buttony = malloc( sizeof( GtkWidget* ) * y );
	//con estos dos for establezco una fila y una columna de botones
	//cuyo rango puede variar de 1 - 99
	set_guide( buttonx, x_label, grid, x, COLUMNA );
	set_guide( buttony, y_label, grid, y, FILA );
	gchar*** label = malloc( sizeof( gchar** ) * x );
	GtkWidget*** celda = set_cells( x, y, label );
	fill_grid( celda, label, grid, window, x, y );
	g_signal_connect( window, "delete_event",G_CALLBACK(gtk_main_quit), NULL );
	//evento de click, uso un puntero a label para modificarlo en la funcion definida
	//arriba, cuando uso G_CALLBACK se llama la funcion con los argumentos button y
	//(gpointer)algo, con lo cual se interactua
	gtk_grid_set_row_spacing( (GtkGrid*)grid, 2 );
	gtk_grid_set_column_spacing( (GtkGrid*)grid, 2 );
	//gtk_grid_set_column_homogeneous( (GtkGrid*)grid, TRUE );
	gtk_grid_set_row_homogeneous( (GtkGrid*)grid, TRUE );
	//estas dos lineas lo hacen adaptable a la pantalla, las celdas
	//siempre tendran el mismo tamaño entre si
	gtk_container_add( (GtkContainer*)window, grid );
	gtk_window_set_title( (GtkWindow*)window, "Hoja de Calculo - Calctech" );
	gtk_widget_show_all( window );
	gtk_main();
    return 0;
}

static void button_clicked( GtkWidget* widget, gpointer data ){
	gtk_button_set_label( (GtkButton*)data, "Kyaaa~ Baka-senpai desu" );
}

void set_label_number( gchar** string, int lim ){
	gint i = 0, j = 0, vuelta = 0;
	if( lim > 99 )
		return;
	for( i = 0; i < lim; i++ ){
		if( i <= 9 ){
			string[i] = malloc( 2 );
			string[i][0] = '0' + i;
			string[i][1] = '\0';
		}else{
			string[i] = malloc( 3 );
			string[i][0] = '1' + vuelta;
			string[i][1] = '0' + j;
			string[i][2] = '\0';
			j++;
			if( j > 9 ){
				j = 0;
				vuelta++;
			}
		}
	}
}

void set_guide( GtkWidget** button, gchar** label, GtkWidget* grid, int lim, int flag ){
	gint i;
	set_label_number( label, lim );
	if( flag == COLUMNA ){
		for( i = 0; i < lim; i++ ){
			button[i] = gtk_button_new_with_label( label[i] );
			gtk_grid_attach( (GtkGrid*)grid, button[i], 2 + i, 1, 1, 1 );
		}
	}else{
		for( i = 0; i < lim; i++ ){
			button[i] = gtk_button_new_with_label( label[i] );
			gtk_grid_attach( (GtkGrid*)grid, button[i], 1, 2 + i, 1, 1 );
		}
	}
}

GtkWidget*** set_cells( int x, int y, gchar*** label ){
	int i;
	GtkWidget*** celda = malloc( sizeof( GtkWidget** ) * x );
	for( i = 0; i < y; i++ ){
		label[i] = malloc( sizeof( gchar* ) * y );
		celda[i] = malloc( sizeof( GtkWidget* ) * y );
	}
	return celda;
}

void fill_grid( GtkWidget*** celda, gchar*** label, GtkWidget* grid, GtkWidget* window, int x, int y ){
	int i, j;
	for( i = 0; i < x; i++ ){
		label[i] = malloc( sizeof( GtkWidget* ) * y ); 
	}
	for( i = 0; i < y; i++ ){
		for( j = 0; j < x; j++ ){
			label[j][i] = "--";
			celda[j][i] = gtk_button_new_with_label( label[j][i] );
			gtk_grid_attach( (GtkGrid*)grid, celda[j][i], 2 + j, 2 + i, 1, 1 );
			g_signal_connect( celda[j][i], "clicked",G_CALLBACK(button_clicked), (gpointer)celda[j][i] );
		}
	}
}
