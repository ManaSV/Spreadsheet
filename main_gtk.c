#include <stdlib.h>
#include <stdio.h>
#include "mathParser.c"
#include <gtk/gtk.h>
#include <glib.h>
#include <gdk/gdkkeysyms.h>
#include <glib/gprintf.h>

enum tipo{ FILA, COLUMNA };

static void button_clicked( GtkWidget* widget, int* data );
void set_label_number( gchar** string, int x );
void set_guide( GtkWidget** button, gchar** label, GtkWidget* grid, int lim, int flag );
GtkWidget*** set_cells( int x, int y, gchar*** content );
void fill_grid( GtkWidget*** celda, gchar*** content, GtkWidget* grid, GtkWidget* window ,int x, int y );
static void update_cell( GtkWidget* window, GdkEventKey* event, int* data );

gchar* label_new; //aqui se guardara el label escrito
GtkWidget*** celda; //aqui estan las celdas declaradas globalmente
int*** location_array; //aqui estan las localizaciones con su boton respectivo
int* location; // aqui se encuentra una localizacion concreta que se
//llena cuando se clickea el boton
GtkWidget* input_window;

int main (int argc, char *argv[]) {
	gtk_init (&argc, &argv);
	gint x, y;
	printf( "INGRESE NUMERO DE COLUMNAS: " );
	scanf( "%d", &x );
	printf( "INGRESE NUMERO DE FILAS: " );
	scanf( "%d", &y );
	location = malloc( sizeof(int) * 2 );
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
	celda = set_cells( x, y, label );
	fill_grid( celda, label, grid, window, x, y );
	g_signal_connect( window, "delete_event",G_CALLBACK(gtk_main_quit), NULL );
	//evento de click, uso un puntero a label para modificarlo en la funcion definida
	//arriba, cuando uso G_CALLBACK se llama la funcion con los argumentos button y
	//(gpointer)algo, con lo cual se interactua
	gtk_grid_set_row_spacing( (GtkGrid*)grid, 2 );
	gtk_grid_set_column_spacing( (GtkGrid*)grid, 2 );
	gtk_grid_set_column_homogeneous( (GtkGrid*)grid, TRUE );
	gtk_grid_set_row_homogeneous( (GtkGrid*)grid, TRUE );
	//estas dos lineas lo hacen adaptable a la pantalla, las celdas
	//siempre tendran el mismo tamaño entre si
	gtk_container_add( (GtkContainer*)window, grid );
	gtk_window_set_title( (GtkWindow*)window, "Hoja de Calculo - Calctech" );
	gtk_widget_show_all( window );
	gtk_main();
    return 0;
}

static void update_cell( GtkWidget* widget, GdkEventKey* event, int* data ){
	if( event->keyval == GDK_KEY_Return ){ //detecta si el key es enter
		label_new = "";
		label_new = g_strconcat( label_new, gtk_entry_get_text( (GtkEntry*)widget ), NULL );
		//concatena la cadena, aqui debera estar la funcion de parsear
		label_new = calculate( label_new );
		gtk_button_set_label( (GtkButton*)celda[location[0]][location[1]], label_new );
		label_new = ""; //regresamos la cadena a una vacia para no contaminar nuevas celdas
		gtk_widget_hide( input_window );
	}
}

static void button_clicked( GtkWidget* widget, int* data ){
	input_window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	gtk_window_set_title( (GtkWindow*)input_window, "Ingrese un valor!" );
	gtk_window_set_default_size( (GtkWindow*)input_window, 300, 50 );
	gtk_container_set_border_width( (GtkContainer*)input_window, 10 );
	GtkWidget* box = gtk_box_new( FALSE, 0 );
	gtk_container_add( (GtkContainer*)input_window, box );
	GtkEntryBuffer* buffer = gtk_entry_buffer_new( NULL, -1 );
	GtkWidget* input = gtk_entry_new();
	gtk_entry_set_buffer( (GtkEntry*)input, buffer );
	gtk_box_pack_start( GTK_BOX( box ), input, TRUE, TRUE, 5 );
	const gchar* temp = gtk_button_get_label( (GtkButton*)widget );
	gtk_entry_set_text( (GtkEntry*)input, temp );
	location[0] = data[0];
	location[1] = data[1];
	g_signal_connect_after( input, "key_release_event", G_CALLBACK( update_cell ), NULL );
	g_printf( "celda %d, %d\n", location[0], location[1] );
	gtk_widget_show_all( input_window );
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
	for( i = 0; i < x; i++ ){
		label[i] = malloc( sizeof( gchar* ) * y );
		celda[i] = malloc( sizeof( GtkWidget* ) * y );
	}
	return celda;
}

void fill_grid( GtkWidget*** celda, gchar*** label, GtkWidget* grid, GtkWidget* window, int x, int y ){
	int i, j;
	location_array = malloc( sizeof(int**) * x );
	for( i = 0; i < x; i++ ){
		label[i] = malloc( sizeof( GtkWidget* ) * y ); 
		location_array[i] = malloc( sizeof( int* ) * y );
	}
	for( i = 0; i < y; i++ ){
		for( j = 0; j < x; j++ ){
			label[j][i] = ""; //para callar el error de label IS NULL
			celda[j][i] = gtk_button_new_with_label( label[j][i] );
			gtk_grid_attach( (GtkGrid*)grid, celda[j][i], 2 + j, 2 + i, 1, 1 );
			location_array[j][i] = malloc( sizeof( int ) * 2 );
			location_array[j][i][0] = j;
			location_array[j][i][1] = i;
			g_signal_connect( celda[j][i], "clicked", G_CALLBACK(button_clicked), location_array[j][i] );
		}
	}
}
