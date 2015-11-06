#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

static void button_clicked( GtkWidget* widget, gpointer data );
void set_label_number( gchar** string, int lim );

int main (int argc, char *argv[]) {
	gtk_init (&argc, &argv);
	gint x, y, i;
	printf( "INGRESE NUMERO DE COLUMNAS: " );
	scanf( "%d", &x );
	printf( "INGRESE NUMERO DE FILAS: " );
	scanf( "%d", &y );
	gchar** x_label = malloc( sizeof( gchar* ) * x );
	gchar** y_label = malloc( sizeof( gchar* ) * y );
	set_label_number( x_label, x );
	set_label_number( y_label, x );
	GtkWidget* window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	GtkWidget** buttonx = malloc( sizeof( GtkWidget* ) * x );
	GtkWidget** buttony = malloc( sizeof( GtkWidget* ) * y );
	GtkWidget* label = gtk_label_new( "Hello world" );
	GtkWidget* grid = gtk_grid_new();
	//con estos dos for establezco una fila y una columna de botones
	//cuyo rango puede variar de 1 - 99
	for( i = 0; i < x; i++ ){
		buttonx[i] = gtk_button_new_with_label( x_label[i] );
		gtk_grid_attach( (GtkGrid*)grid, buttonx[i], i + 1, 1, 1, 1 );
	}
	for( i = 0; i < y; i++ ){
		buttony[i] = gtk_button_new_with_label( y_label[i] );
		gtk_grid_attach( (GtkGrid*)grid, buttony[i], 1, i + 1, 1, 1 );
	}
	g_signal_connect( window, "delete_event",G_CALLBACK(gtk_main_quit), NULL );
	g_signal_connect( buttonx[0], "clicked", G_CALLBACK( button_clicked ), (gpointer)label );
	//evento de click, uso un puntero a label para modificarlo en la funcion definida
	//arriba, cuando uso G_CALLBACK se llama la funcion con los argumentos button y
	//(gpointer)label
	gtk_grid_attach( (GtkGrid*)grid, label, 3, 2, 1, 1 );
	gtk_grid_set_row_spacing( (GtkGrid*)grid, 2 );
	gtk_grid_set_column_spacing( (GtkGrid*)grid, 2 );
	gtk_grid_set_column_homogeneous( (GtkGrid*)grid, TRUE );
	gtk_grid_set_row_homogeneous( (GtkGrid*)grid, FALSE );
	gtk_window_set_default_size( (GtkWindow*)window, 300, 200 );
	gtk_container_add( (GtkContainer*)window, grid );
	gtk_window_set_title( (GtkWindow*)window, "Senpai simulator 2015" );
	gtk_widget_show_all( window );
	gtk_main();
    return 0;
}

static void button_clicked( GtkWidget* widget, gpointer data ){
	gtk_label_set_text( (GtkLabel*)data, "Kyaaa~ Baka-senpai desu" );
}

void set_label_number( gchar** string, int lim ){
	int i, j = 0, vuelta = 0;
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
