#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>

using namespace std;
int q=1;
int n;
int a[1000000];
int f[1000000];
int c[1000000];
int main() {
	freopen("pdd.in", "r", stdin);
	freopen("pdd.out", "w", stdout);
	scanf("%d",&n);

	for(int i=1; i<=n; i++) {
		scanf("%d",&a[i]);
	}
	int ans=1;
	for(int i=1; i<=n; i++) {
		int k=1;
		f[k]=a[i];
		for(int j=i; j<=n; j++) {
			if(i!=j && f[k]<a[j]) {
				k++;
				f[k]=a[j];
			}

			else {
				int l=1;
				int r=k;
				if(l==r)break;
				while(l<r) {
					int mid=(l+r)/2;

					if(f[mid]<=a[j]) {
						l=mid+1;
					}

					else {
						r=mid;
					}

				}
				f[l]=a[j];
			}
		}

		a[q]=k;
		q++;

	}

	q--;

	int maxn=-1;

	for(int i=1; i<=q; i++) {
		if(a[i]>maxn)maxn=a[i];
	}

	printf("%d\n",maxn);


	for(int i=1; i<=q; i++) {
		printf("%d",a[i]);
		if(i<q) {
			printf(" ");
		}
	}

}


