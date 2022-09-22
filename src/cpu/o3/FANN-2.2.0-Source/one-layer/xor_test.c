/*
Fast Artificial Neural Network Library (fann)
Copyright (C) 2003-2012 Steffen Nissen (sn@leenissen.dk)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <stdio.h>

#include "fann.h"

int main()
{

 //   struct fann *net;              /* your trained neural network */























	fann_type *calc_out;
	unsigned int i;
	int ret = 0;

	struct fann *ann;
	struct fann_train_data *data;

	printf("Creating network.\n");

//#ifdef FIXEDFANN
//	ann = fann_create_from_file("xor_fixed.net");
//#else
	ann = fann_create_from_file("spectre.net");
//#endif

	if(!ann)
	{
		printf("Error creating ann --- ABORTING.\n");
		return -1;
	}

	fann_print_connections(ann);
	fann_print_parameters(ann);


	/////
	struct fann_connection *con;   /* weight matrix */
	    unsigned int connum;           /* connections number */
	    size_t my;

	    /* Insert your net allocation and training code here */


	    connum = fann_get_total_connections(ann);
	    if (connum == 0) {
	        fprintf(stderr, "Error: connections count is 0\n");
	        return EXIT_FAILURE;
	    }

	    con = calloc(connum, sizeof(*con));
	    if (con == NULL) {
	        fprintf(stderr, "Error: unable to allocate memory\n");
	        return EXIT_FAILURE;
	    }

	    /* Get weight matrix */
	    fann_get_connection_array(ann, con);

	    /* Print weight matrix */
	    for (my = 0; my < connum; ++my) {
	        printf("weight from %u to %u: %f\n", con[my].from_neuron,
	               con[my].to_neuron, con[my].weight);
	    }

	    free(con);

	printf("Testing network.\n");

//#ifdef FIXEDFANN
//	data = fann_read_train_from_file("xor_fixed.data");
//#else
	data = fann_read_train_from_file("spectre.data");
//#endif

	for(i = 0; i < fann_length_train_data(data); i++)
	{
		fann_reset_MSE(ann);
		calc_out = fann_test(ann, data->input[i], data->output[i]);
#ifdef FIXEDFANN
		printf("SPECTRE test (%d, %d) -> %d, should be %d, difference=%f\n",
			   data->input[i][0], data->input[i][1], calc_out[0], data->output[i][0],
			   (float) fann_abs(calc_out[0] - data->output[i][0]) / fann_get_multiplier(ann));

		if((float) fann_abs(calc_out[0] - data->output[i][0]) / fann_get_multiplier(ann) > 0.2)
		{
			printf("Test failed\n");
			ret = -1;
		}
#else
		printf("SPECTRE test (%f, %f) -> %f, should be %f, difference=%f\n",
			   data->input[i][0], data->input[i][1], calc_out[0], data->output[i][0],
			   (float) fann_abs(calc_out[0] - data->output[i][0]));
#endif
	}

	printf("Cleaning up.\n");
	fann_destroy_train(data);
	fann_destroy(ann);

	return ret;
}
