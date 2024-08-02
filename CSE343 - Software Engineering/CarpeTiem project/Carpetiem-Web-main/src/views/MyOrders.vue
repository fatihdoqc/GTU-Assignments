<template>
<div class="container d-flex flex-column flex-grow-1">
        <div class="row justify-content-center" >
        
            <ul v-if="show" class="col-10 col-sm-4 d-flex d-sm-block flex-column " >
                <li v-for="item in carpets" :key='item.area' class = "card mx-3 my-3">  
                        <div class="row g-0">
                            <div class="col-sm-4">
                                <img src="https://firebasestorage.googleapis.com/v0/b/hali-4cdae.appspot.com/o/LOGO.png?alt=media&token=c37f9ffd-49d2-429b-b246-4048053c8764" class="img-fluid rounded-start w-100" />
                            </div>
                            <div class="col-sm-8">
                            <div class="card-body">
                                <h5 class="card-title"> {{  }} </h5>
                                <p class="card-text">
                                <b>Alanı: </b> {{ item.area }} m2
                                </p>
                                <p class="card-text">
                                <b>Tipi: </b>{{ item.type }}
                                </p>
                                <p class="card-text">
                                <b>Durumu: </b>{{ item.status }} 
                                </p>
                            </div>
                        </div>
                    </div>

                </li>
            </ul>           
        </div>
</div>
</template>

<script>
import { ref } from "@vue/reactivity";
import firebase from "firebase/compat/app";
import "firebase/compat/auth";
import db from "../firebase";
import { onBeforeMount } from '@vue/runtime-core';

export default {
  name: "App",

  setup(){

      const carpets = ref([]);
      const show = ref(false);

      onBeforeMount( async () => {
          try{
            var carpet_col = await db.collection("carpets").where("customer_id", "==", firebase.auth().currentUser.uid).get();

            carpet_col.forEach((doc) => {
                var obj = {};
                    obj["area"] = doc.data().area;
                    obj["type"] = doc.data().type;
                    obj["status"] = doc.data().status;

                    carpets.value.push(obj);
            })

            console.log(carpets);
            show.value = true;
          } 
             catch(error){
                console.log("Error getting documents: ", error);
            }
      } );
      

        /*function append_list(str) {
            var order_l = document.getElementById("order_list");
            var card_body = document.createElement("div");
            var card = document.createElement("div");
            var card_title = document.createElement("h5");

            card.setAttribute("class" , "card");
            card_body.setAttribute("class" , "card-body");
            card_title.setAttribute("class" , "card-title");
            card_title.innerText = "";

            card.appendChild(card_title);  
            card.appendChild(document.createTextNode(str));
            order_l.appendChild(card);          
        }*/

        return {
            carpets,
            show,
        };
  }
}
</script>

<style scoped>
    @media (max-width: 576px) {
        .card img {
            border-bottom-left-radius: 0 !important;
            border-top-left-radius: 0.25rem !important;
            border-top-right-radius: 0.25rem !important;
        }
    }

    .card:not(.skeleton-card) {
    transition: transform 350ms ease-in-out;
    }

    .card:not(.skeleton-card):hover {
    box-shadow: 0 10px 25px 5px hsl(120, 12.5%, 70%);
    background-color: hsl(120, 12.5%, 67%);
    transform: scale(1.025);
    }
</style>
