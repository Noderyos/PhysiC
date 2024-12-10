#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    double x,y;
} V2d;

V2d v2d(double x, double y);
V2d v2dd(double xy);

V2d v2d_add(V2d v1, V2d v2);
V2d v2d_sub(V2d v1, V2d v2);
V2d v2d_mul(V2d v1, V2d v2);
V2d v2d_div(V2d v1, V2d v2);


#endif

#ifdef VECTOR_IMPLEMENTATION
#undef VECTOR_IMPLEMENTATION

V2d v2d(double x, double y){
    return (V2d){x, y};
}

V2d v2dd(double xy){
    return (V2d){xy, xy};
}

V2d v2d_add(V2d v1, V2d v2){
    return (V2d){v1.x+v2.x, v1.y+v2.y};
}

V2d v2d_sub(V2d v1, V2d v2){
    return (V2d){v1.x-v2.x, v1.y-v2.y};
}

V2d v2d_mul(V2d v1, V2d v2){
    return (V2d){v1.x*v2.x, v1.y*v2.y};
}

V2d v2d_div(V2d v1, V2d v2){
    return (V2d){v1.x/v2.x, v1.y/v2.y};
}


#endif
