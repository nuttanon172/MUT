<script setup>
import Student from '../components/Student.vue';
</script>

<template>
    <div>
        <h1>Hello MUT!</h1>
        <Student name="Natthanon" lname="Tairattanapong"></Student>
    </div>
</template>
<script>
export default {
    componencts:{
        Student
    }
}
</script>
<style scoped>
    h1{
        color: red;
    }
</style>