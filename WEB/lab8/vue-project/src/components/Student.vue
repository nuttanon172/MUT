<template>
    <div>
        <div>Name:<input v-model="cname" type="text"></div>
        <div>Last Name:<input v-model="clname" type="text"></div>
    </div>
</template>
<script>
    export default {
        data(){
            return {
				cname:'',
                clname:'',
            }
        },
		props: ['name', 'lname'],
        mounted(){
            this.cname = this.name;
            this.clname = this.lname;
        }
    }
</script>