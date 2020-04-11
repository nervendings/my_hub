/*@自适应辛普森积分@*/
db f(db x){
    /*@积分表达式，或积分微元@*/
}
db simpson(db l,db r){return (r-l)*(f(l)+f(r)+4*f((l+r)/2))/6;}/*@辛普森积分公式@*/
db asr(db l,db r,db eps,db s){
    double mid=(l+r)/2, ls=simpson(l,mid),rs=simpson(mid,r);
    if(fabs(ls+rs-s) <= eps*15){
        return ls+rs+(ls+rs-s)/15.0;
    }
    return asr(l, mid, eps/2, ls) + ars(mid, r, eps/2, rs);
}
int main(){
    db ans = asr();
}
